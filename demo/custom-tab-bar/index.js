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
        selectedIconPath:"home"
      },
      {
        "pagePath": "/pages/AI/AI",
        "text":"拍照识别",
        iconPath:"search",
        selectedIconPath:"search"
      },
      {
        "pagePath": "/pages/random/random",
        "text":"吃啥哟",
        iconPath:"friends-o",
        selectedIconPath:"friends"
      },
      {
        "pagePath": "/pages/my/my",
        "text":"我",
        iconPath:"setting-o",
        selectedIconPath:"setting"
      }
    ]
  },
  methods:{
    onChange(e){
      let index = e.detail;
      this.setData({
        active:index
      })
      //切换页面
      wx.switchTab({
        url:this.data.list[index].pagePath
      })
   }
  }
   
  
})