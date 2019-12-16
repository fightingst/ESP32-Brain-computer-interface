//module.export=
class BlueSnowBci{
  constructor(){
    var self=this
    self.esp32Ws='192.168.2.154:81'
    const app=require('express')()
    const jsonParser=require('body-parser').json()
    app.get('/',(req,res)=>{res.sendFile(__dirname+'/client/index.html')})
    app.post('/',jsonParser,(req,res)=>{handleReq(req,res)})
    app.listen(3000,'localhost',()=>console.log("http://localhost:3000"))
    const WebSocketClient=require('websocket').client
    var esp32Client=new WebSocketClient()
    esp32Client.on('connectFailed',(err)=>{
      console.log(err); esp32Client.connect("ws://"+self.esp32Ws)})
    esp32Client.on('connect',(connection)=>{
      connection.on('message',(message)=>{
        self.registerPair("esp32",message.utf8Data)
      })
    }).connect("ws://"+self.esp32Ws)
    self.ioHook=require('iohook').on("keypress",(e)=>{
      self.registerPair("keypress",e.rawcode)
    }).start()
    self.pair={esp32:null,keypress:null}
  }

  handleReq(req,res){

  }
  registerPair(key,item){
    var self=this
    // to do: create time stamp!
  }
}

blueSnowBci = new BlueSnowBci()
