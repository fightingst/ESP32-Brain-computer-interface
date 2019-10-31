
class SimpleBCI{
	constructor(plotlyId,datguiId,pinToChannel){
		var self = this
		self.plotlyId = plotlyId
		self.pinToCh=pinToChannel
		self.channels = []
		for(var i=0;i<Object.keys(self.pinToCh).length;i++){
			self.channels.push({
				x:[...Array(200).keys()],y:[...Array(200).keys()],
				mode:'lines',type:'scatter'
			})
		}
		Plotly.plot(self.plotlyId,self.channels)

		self.guiData={
			sampleInterval:100,
			tolerance:10,
			memSize:6000,

			pin:34,
		}
		self.gui = new dat.GUI({autoPlace:false})
		self.gui.add(self.guiData,'sampleInterval',10,1000).onFinishChange(
			()=>self.handleGuiData()).step(10)
		self.gui.add(self.guiData,'tolerance',1,10).onFinishChange(
			()=>self.handleGuiData()).step(1)
		self.gui.add(self.guiData,'memSize',100,6000).onFinishChange(
			()=>self.handleGuiData()).step(100)
		document.querySelector(datguiId).appendChild(self.gui.domElement)

		self.connection=null
	}

	handleGuiData(){
		var self=this
		if(self.connection)
		self.connection.send("guiData:"+JSON.stringify(self.guiData))
	}

	onMessage(msg){
		var self = this
		console.log(msg)
		var data = JSON.parse(msg.split('analogRead:')[1])
		var ch = self.pinToCh[data.pin]
		self.channels[ch].y=data.values
		//console.log(self.channels)
		Plotly.newPlot(self.plotlyId,self.channels)
		//Plotly.react(self.plotlyId,{data: self.channels})
	}
}
