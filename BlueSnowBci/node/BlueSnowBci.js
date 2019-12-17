//module.export=
class BlueSnowBci{
  constructor(){
    var self=this
    self.settings={esp32Ws:'192.168.2.154:81'}
    const app=require('express')()
    const jsonParser=require('body-parser').json()
    app.get('/',(req,res)=>{res.sendFile(__dirname+'/client/index.html')})
    app.post('/',jsonParser,(req,res)=>{handleReq(req,res)})
    app.listen(3000,'localhost',()=>console.log("http://localhost:3000"))

    const WebSocketClient=require('websocket').client
    var esp32Client=new WebSocketClient()
    esp32Client.on('connectFailed',(err)=>{console.log(err)
      esp32Client.connect("ws://"+self.settings.esp32Ws)}
    )
    esp32Client.on('connect',(connection)=>{
      self.connection=connection
      connection.on('message',(message)=>{
        self.record("esp32",message.utf8Data)
      })
    }).connect("ws://"+self.settings.esp32Ws)

    self.ioHook=require('iohook').on("keypress",(e)=>{
      self.record("keypress",e.rawcode)
    }).start()
  }

  handleReq(req,res){
    if(req.body.set){
      self.connection.sendUTF(JSON.stringify(req.body.set.esp32))
      self.settings=req.body.set.server
    }
    if(req.body.get){
      res.send("fake data")
    }
  }

  record(key,item){
    var self=this
    // to do: create time stamp!
  }

  analyse(message){
    var self=this
    // to do: use python subprocess!
  }
}

blueSnowBci = new BlueSnowBci()
