// pages/random/random.js
Page({
  onShow(){
      this.getTabBar().setData({
        active: 2
      })
    },
    data: {
      size:{ //转盘大小可配置
         w:599,
         h:600
      },//转盘大小,
      musicflg: true, //声音
      fastJuedin: false,//快速决定
      repeat: false,//不重复抽取
      probability: false,// 概率
      s_awards: '?',//结果
      option: '标题',
      id:'?',
      liebiao:'',
      //转盘的总数据，想添加多个可以往这数组里添加一条格式一样的数据
      xiaojuedingArr: [
         {
            id: 0,
            option: '',//转盘的标题名称
            awards: [
               {
                  id: 0,                // id递增
                  name: "P座点绽",           // 选项名 超过9个字时字体会变小点 大于13个数时会隐藏掉超出的
                  color: '#FFA827',    // 选项的背景颜色
                  probability: 10       // 概率 0代表永远也转不到这个选项，数字越大概率也就越大,data中的probability属性设置为true时是才生效, 这属性也必须填写，不填写会出错
               },
               {
                  id: 1,
                  name: "厨艺天地",
                  color: '#AA47BC',
                  probability: 10
               },
               {
                  id: 2,
                  name: "点聚",
                  color: '#42A5F6',
                  probability: 10
               },
               {
                  id: 3,
                  name: "711便利店",
                  color: '#00FFFF',
                  probability: 10
               },
               {
                  id: 4,
                  name: "OK便利店",
                  color: '#FF00FF',
                  probability: 10
               },
               {
                  id: 5,
                  name: "金拱门",
                  color: '#FFE4B5',
                  probability: 10
               }
                    
      ]}]
    },
    //接收当前转盘初始化时传来的参数
    getData(e) {
      this.setData({
         option: e.detail.option
      })
   },
 
   //接收当前转盘结束后的答案选项
   getAwards(e) {
      this.setData({
         s_awards: e.detail.end ? "?" : e.detail.s_awards,
         // id:e.detail.id,
         
      })
   },
 
   //开始转动或者结束转动
   startZhuan(e) {
      
      // if(f == 0){
      //    a = Math.floor(Math.random()*7)
      //    console.log(a)
      //    f = 1
      // }else{
      //    f = 0
      // }
      this.setData({
         zhuanflg: e.detail ? true : false
      })
   },
 
   //切换转盘选项
   switchZhuanpan(e) {
      //当转盘停止时才执行切换转盘
      if (!this.data.zhuanflg) {
         var idx = e.currentTarget.dataset.idx, zhuanpanArr = this.data.zhuanpanArr, obj = {};
         for (let i in zhuanpanArr) {
            if (this.data.option != zhuanpanArr[i].option && zhuanpanArr[i].id == idx) {
               obj.option = zhuanpanArr[i].option;
               obj.awards = zhuanpanArr[i].awards;
               this.setData({
                  awardsConfig: obj //其实默认要更改当前转盘的数据要传个这个对象，才有效果
               })
               break;
            }
         }
      }
   },
 
 
   onLoad: function () {
       //实例化组件对象，这样有需要时就能调用组件内的方法
       this.zhuanpan = this.selectComponent("#zhuanpan");
 
       //可以这样调用 示例：this.zhuanpan.switchZhuanpan(data); 
       //上面这方法可用来切换转盘选项数据，参数可以看组件构造器中的switchZhuanpan方法
   }
 })
