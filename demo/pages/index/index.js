// index.js
var app = getApp() 
 Page({ 
   onShow(){
     this.getTabBar().setData({
       active: 0
     })
   },
  data: {
    swiperH: '',//swiper高度
    nowIdx: 0,//当前swiper索引
    bnrUrl: [//图片列表
      "https://pic3.zhimg.com/v2-9f4d07deec067b02c8ba71091de0669e_r.jpg",
      "https://pic4.zhimg.com/v2-feb3698945633cc5ead0d142199d136f_r.jpg",
      "https://pic1.zhimg.com/v2-b739a2b1c873f11b4b402ab0128c60a8_r.jpg",
      "https://pic4.zhimg.com/v2-e49a779f30f298c86145bd507d9e030f_r.jpg"
    ]
  },
  //获取swiper高度
  getHeight: function (e) {
    var winWid = wx.getSystemInfoSync().windowWidth - 130;//获取当前屏幕的宽度
    var imgh = 400;//图片高度
    var imgw = e.detail.width;
    var sH = winWid * imgh / imgw + "px"
    this.setData({
      swiperH: 400//设置高度
    })
  },
  //swiper滑动事件
  swiperChange: function (e) {
    this.setData({
      nowIdx: e.detail.current
    })
  }
 /*data: { 
 movies:[
  {url:'https://ss1.bdstatic.com/70cFuXSh_Q1YnxGkpoWK1HF6hhy/it/u=113624493,1741206956&fm=26&gp=0.jpg'} , 
  {url:'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fqcloud.dpfile.com%2Fpc%2Fv-ktDf0PojdMgBh6Q7KwNW-es7V6gH7pLhxuj6WthstiWRr1Oyx9E1Ltd1LLhGf7joJrvItByyS4HHaWdXyO_DrXIaWutJls2xCVbatkhjUNNiIYVnHvzugZCuBITtvjski7YaLlHpkrQUr5euoQrg.jpg&refer=http%3A%2F%2Fqcloud.dpfile.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1617087210&t=6b19aa5b6083c21e730ad809b726901a'}
] 
}, 
  onLoad: 
  function () 
  { 
  } */


}) 
