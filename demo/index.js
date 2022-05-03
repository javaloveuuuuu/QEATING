// components/custom-tab-bar/index.js
Component({
  
  /**
   * 页面的初始数据
   */
  data: {
     //当前页
     active: 0,
      "list": [
      {
        "pagePath": "/pages/index/index",
        "text":"首页",
        iconPath:"home-o",
      },
      {
        "pagePath": "/pages/AI/AI",
        "text":"拍照识别",
        iconPath:"search",
      },
      {
        "pagePath": "/pages/random/random",
        "text":"吃啥哟",
        iconPath:"friends-o",
      },
      {
        "pagePath": "/pages/daka/daka",
        "text":"签到",
        iconPath:"label-o",
      },
      {
        "pagePath": "/pages/my/my",
        "text":"我",
        iconPath:"setting-o",
      }
    ]
  },
  methods:{
    onChange(event){
      this.setData({
        active:event.detail
      })
      //切换页面
      wx.switchTab({
        url:this.data.list[event.detail].pagePath
      })
   }
  }
   
  
  
})