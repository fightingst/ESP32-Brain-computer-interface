
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
		self.channelsFiltered=[{}]

		self.guiData={
			sampleInterval:100,memSize:1000,
			fMax:100,
			typeFilt:'lowPass',fLowFilt:40,fHighFilt:100,
			pin:34,
			test:true,testFreq:66}
		self.gui=new dat.GUI()
		self.gui.add(self.guiData,'sampleInterval',50,1000)
			.step(10).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'memSize',100,2000)
			.step(100).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'fMax',50,300)
			.step(1).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'typeFilt',['lowPass','bandStop'])
			.onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'fLowFilt',1,200)
			.step(1).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'fHighFilt',1,200)
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
		var signal=new Signal(values,self.tAxis)
		self.channels[ch].x=self.tAxis
		self.channels[ch].y=values
		Plotly.newPlot(self.signalPlot,self.channels)
		signal.getDft(values,(dft)=>{
			self.channelsDft[ch].x=self.fAxis.slice(0,self.fAxisSliceN)
			self.channelsDft[ch].y=dft.slice(0,self.fAxisSliceN)
			Plotly.newPlot(self.dftPlot,self.channelsDft)
		})
		signal.filter(self.guiData.typeFilt,
			self.guiData.fHighFilt,
			self.guiData.fLowFilt,(filtered)=>{
			self.channelsFiltered[ch].x=self.tAxis
			self.channelsFiltered[ch].y=filtered
			Plotly.newPlot(self.filteredPlot,self.channelsFiltered)
		})
	}
}

class Signal{
	constructor(values,tAxis){
		var self=this; self.values=values
		self.tAxis=tAxis; self.N=tAxis.length
	}

	getDft(values,callback){
		var real=tf.tensor1d(values)
		real=real.sub(real.mean())
		var imag=tf.zerosLike(real)
		var dft=tf.complex(real,imag).fft().abs()
		dft=dft.div(dft.max())
		dft.data().then((dft)=>{callback(dft)})
	}

	filter(type,fHigh,fLow,callback){
		var self=this; var filtered=[]
		for(var i=0;i<self.N;i++){
			var sum=0
			for(var k=0;k<self.N;k++){
				//use unnormalized sinc function in physics!
				var arg=2*Math.PI*fLow*(self.tAxis[i]-self.tAxis[k])
				if(arg==0) sum+=self.values[k]
				else sum+=self.values[k]*Math.sin(arg)/arg
			}
			filtered.push(2*fLow*sum)
		}
		callback(filtered)
	}
}
