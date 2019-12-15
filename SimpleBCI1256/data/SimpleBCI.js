
class SimpleBCI{
	constructor(pinToChannel){
		var self = this
		self.signalPlot='signalPlot'
		self.dftPlot='dftPlot'
		self.filteredPlot='filteredPlot'
		self.guiDiv='#guiDiv'
		self.pinToCh=pinToChannel

		self.connection=null
		self.channels=[]
		for(var i=0;i<16;i++) self.channels.push({})
		self.channelsDft=self.channels
		self.channelsFiltered=self.channels

		self.guiData={
			sampleInterval:1000,memSize:200,
			fMax:100,
			typeFilt:'lowPass',fLowFilt:30,fHighFilt:100,
			pin:34,
			test:true,testFreq:50,
			yScale:21}
		self.gui=new dat.GUI()
		self.gui.add(self.guiData,'sampleInterval',500,10000)
			.step(10).onFinishChange(()=>self.guiChange())
		self.gui.add(self.guiData,'memSize',100,1000)
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
		self.gui.add(self.guiData,'yScale',1,24)
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
		var self = this
		var data=JSON.parse(msg); console.log(data)
		var ch
		if(data.chip2) for(ch=0;ch<8;ch++) self.analyse(ch,data.chip2[ch])
	}

	analyse(ch,values){
		var self=this
		//var signal=new Signal(values,self.tAxis)
		self.channels[ch].x=self.tAxis; self.channels[ch].y=values
		var layout={yaxis:{range:[0,Math.pow(2,self.guiData.yScale)]}}
		Plotly.react(self.signalPlot,self.channels,layout)
		/*
		signal.filter(self.guiData.typeFilt,
			self.guiData.fHighFilt,
			self.guiData.fLowFilt,(filtered)=>{
			self.channelsFiltered[ch].x=self.tAxis
			self.channelsFiltered[ch].y=filtered
			//Plotly.react(self.filteredPlot,self.channelsFiltered)
			signal.getDft(filtered,(dft)=>{
				self.channelsDft[ch].x=self.fAxis.slice(0,self.fAxisSliceN)
				self.channelsDft[ch].y=dft.slice(0,self.fAxisSliceN)
				Plotly.react(self.dftPlot,self.channelsDft)
			})
		})
		*/
	}
}

class Signal{
	constructor(values,tAxis){
		var self=this; var sum=0; self.N=values.length
		for(var i=0;i<self.N;i++) sum+=values[i]
		self.values=values.map(value=>value-sum/self.N)
		self.tAxis=tAxis
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
