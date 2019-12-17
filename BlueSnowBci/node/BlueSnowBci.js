//module.export=
class BlueSnowBci{
  constructor(){
    var self=this
    self.settings={esp32Ws:'192.168.2.154:81',deltaT:100}
    const app=require('express')()
    const jsonParser=require('body-parser').json()
    app.get('/',(req,res)=>{res.sendFile(__dirname+'/client/index.html')})
    app.post('/',jsonParser,(req,res)=>{self.handleReq(req,res)})
    app.listen(3000,'localhost',()=>console.log("http://localhost:3000"))

    const WebSocketClient=require('websocket').client
    var esp32Client=new WebSocketClient()
    esp32Client.on('connectFailed',(err)=>{console.log(err)
      esp32Client.connect("ws://"+self.settings.esp32Ws)
    })
    esp32Client.on('connect',(connection)=>{
      self.connection=connection
      connection.on('message',(message)=>{
        self.record("esp32",JSON.parse(message.utf8Data))
      })
    }).connect("ws://"+self.settings.esp32Ws)

    self.ioHook=require('iohook').on("keypress",(e)=>{
      self.record("keypress",{code:e.rawcode})
    }).start()
  }

  handleReq(req,res){
    var self=this
    if(req.body.set){
      self.connection.sendUTF(JSON.stringify(req.body.set.esp32))
      self.settings=req.body.set.server
    }
    if(req.body.get && self.currentEsp32msg){
      var options=req.body.get; var esp32msg=self.currentEsp32msg
      self.currentEsp32msg=null
      self.analyse(options,esp32msg,(buffer)=>{
        res.send(buffer); console.log("sent")
      })
    }
  }

  record(key,item){
    var self=this; if(key=="esp32") self.currentEsp32msg=item
    item.date=new Date()
    var fs = require('fs').appendFile(
      "dt/"+key,JSON.stringify(item)+"\n",(e)=>{})
  }

  recordPair(key,item){
    var self=this; if(key=="esp32") self.currentEsp32msg=item
    var date=new Date()
    if(self.lastTime) var diff=Math.abs(date-self.lastTime)
    self.lastTime=date
    // state machine
    if(!self.rec) self.rec={}; if(!self.state) self.state="idle"
    if(self.state=="idle" && key=="esp32"){
      self.rec.esp32="..."; self.state="esp32done"
    }
    else if(self.state=="esp32done" && key=="keypress"){
      if(diff<self.settings.deltaT){
        self.rec.keypress=item; self.rec.diff=diff
        self.rec.date=date; console.log(self.rec)
      }
      self.state="idle"; self.rec=null
    }
    console.log(self.state+"  "+diff)
  }

  analyse(options,esp32msg,callback){
    var self=this
    const spawn=require("child_process").spawn
    const py=spawn('python3',["minAnalyse.py",
      JSON.stringify(options),JSON.stringify(esp32msg)])
      .stdout.on('data',(buffer)=>{callback(buffer)})
  }
}

blueSnowBci = new BlueSnowBci()
