
class SimpleBCI{
	constructor(pinToChannel){
		var self = this
		self.signalPlot='signalPlot'
		self.dftPlot='dftPlot'
		self.filteredPlot='filteredPlot'
		self.guiDiv='#guiDiv'
		self.pinToCh=pinToChannel

		self.connection=null
		self.channels=[{}]; self.channelsDft=[{}]

		self.guiData={
			sampleInterval:100,tolerance:10,memSize:1000,
			fMax:100,
			pin:34,
			test:true,testFreq:66}
		self.gui=new dat.GUI()
		self.gui.add(self.guiData,'sampleInterval',50,1000)
			.step(10).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'tolerance',1,20)
			.step(1).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'memSize',100,2000)
			.step(100).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'fMax',50,300)
			.step(1).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'test')
			.onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'testFreq',1,200)
			.step(1).onFinishChange(()=>self.guiChange())
		self.guiChange()
	}

	guiChange(){
		var self = this
		if(self.connection) self.connection.send(
			"guiData:"+JSON.stringify(self.guiData))
		self.dt=self.guiData.sampleInterval/1e6
		self.N=self.guiData.memSize
		self.nAxis=[...Array(self.N).keys()]
		self.tAxis=self.nAxis.map(n=>n*self.dt)
		self.testSignal=self.tAxis.map(t=>Math.sin(6.28*self.guiData.testFreq*t))
		self.fAxis=self.nAxis.map(n=>n/(self.N*self.dt))
		self.fAxisSliceN=self.guiData.fMax*(self.N*self.dt)
		if(self.guiData.test) self.analyse(0,self.testSignal)
	}

	onMessage(msg){
		var self = this; console.log(msg)
		var data=JSON.parse(msg.split('analogRead:')[1])
		self.analyse(self.pinToCh[data.pin],data.values)
	}

	analyse(ch,values){
		var self=this
		var signal=new Signal(values)
		self.channels[ch].x=self.tAxis
		self.channels[ch].y=values
		Plotly.newPlot(self.signalPlot,self.channels)
		self.channelsDft[ch].x=self.fAxis.slice(0,self.fAxisSliceN)
		self.channelsDft[ch].y=signal.getDft().slice(0,self.fAxisSliceN)
		Plotly.newPlot(self.dftPlot,self.channelsDft)
	}
}

class Signal{
	constructor(values){
		var self=this
		self.values=values
	}

	getDft(){
		var self=this
		self.real=tf.tensor1d(self.values)
		self.real=self.real.sub(self.real.mean())
		self.imag=tf.zerosLike(self.real)
		self.dft=tf.complex(self.real,self.imag).fft().abs()
		self.dft=self.dft.div(self.dft.max())
		return self.dft.dataSync()
	}
}
