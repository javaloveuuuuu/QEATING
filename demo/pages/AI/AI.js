// pages/AI/AI.js
Page({
  onShow(){
    this.getTabBar().setData({
      active: 1
    })
  },
 	chooseImg: function () {//图片上传处理函数  
    	    that.setData({  
    	      ishow: false,  
    	      content: ''  
    	    });  
    	    wx.chooseImage({  
    	      count: 1,  
    	      sizeType: ['original', 'compressed'],  
    	      sourceType: ['album', 'camera'],  
    	      success(res) {  
    	        const tempFilePaths = res.tempFilePaths[0];  
    	        that.getB64ByUrl(tempFilePaths);  
    	        that.setData({  
              img: tempFilePaths  
    	        });  
    	      }  
    	    })  
    	  }  
    
    
})