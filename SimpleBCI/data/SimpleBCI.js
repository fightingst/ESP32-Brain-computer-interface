
class SimpleBCI{
	constructor(plotlyId,datguiId){
		var self = this
		self.plotlyId = plotlyId
		self.pinToCh={34:0, 35:1}
		self.channels = []
		for(var i=0;i<Object.keys(self.pinToCh).length;i++){
			self.channels.push({
				x:[...Array(200).keys()],y:[...Array(200).keys()],
				mode:'lines',type:'scatter'
			})
		}
		Plotly.plot(self.plotlyId,self.channels)

		self.guiData={sampleRate:1}
		self.gui = new dat.GUI({autoPlace:false})
		self.gui.add(self.guiData,'sampleRate',0,1000).onFinishChange(
			()=>self.handleGuiData()).step(1)
		document.querySelector(datguiId).appendChild(self.gui.domElement)

		self.connection=null
		self.runRoutine=setInterval(()=>{
			self.sendAnalogRead()
		},10)
	}

	handleGuiData(){
		var self = this
		clearInterval(self.runRoutine)
		self.runRoutine=setInterval(()=>{
			self.sendAnalogRead()
		},self.guiData.sampleRate)
	}

	sendAnalogRead(){
		var self = this
		if(self.connection){
			Object.keys(self.pinToCh).forEach((item)=>{
				self.connection.send("analogRead:"+JSON.stringify({pin:item}))
			})
		}
	}

	onMessage(msg){
		var self = this
		var data = JSON.parse(msg.split('analogRead:')[1])
		var ch = self.pinToCh[data.pin]
		self.channels[ch].y.shift()
		self.channels[ch].y.push(data.value)
		//console.log(self.channels)
		Plotly.newPlot(self.plotlyId,self.channels)
		//Plotly.react(self.plotlyId,{data: self.channels})
	}
}
