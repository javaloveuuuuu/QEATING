//index.js
//获取应用实例
var app = getApp();
var that = '';
Page({
  data: {
    img: 'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1587310931901&di=c1f95abf9f41b62de2fce89f649ec516&imgtype=0&src=http%3A%2F%2Fcp1.douguo.com%2Fupload%2Fcaiku%2F8%2F5%2F2%2Fyuan_855a8baf3c5ec47a9c2a2517a0728562.jpeg',
    imgB64: '',
    content: '',
    ishow: false,
    circleList: [],
    colorCircleFirst: '#FFDF2F',
    colorCircleSecond: '#FE4D32',
  },
  onLoad: function (options) {
    that = this;
    var leftCircle = 7.5;
    var topCircle = 7.5;
    var circleList = [];
    for (var i = 0; i < 24; i++) {
      if (i == 0) {
        topCircle = 15;
        leftCircle = 15;
      } else if (i < 6) {
        topCircle = 7.5;
        leftCircle = leftCircle + 102.5;
      } else if (i == 6) {
        topCircle = 15
        leftCircle = 620;
      } else if (i < 12) {
        topCircle = topCircle + 94;
        leftCircle = 620;
      } else if (i == 12) {
        topCircle = 565;
        leftCircle = 620;
      } else if (i < 18) {
        topCircle = 570;
        leftCircle = leftCircle - 102.5;
      } else if (i == 18) {
        topCircle = 565;
        leftCircle = 15;
      } else if (i < 24) {
        topCircle = topCircle - 94;
        leftCircle = 7.5;
      } else {
        return
      }
      circleList.push({ topCircle: topCircle, leftCircle: leftCircle });
    }
    that.setData({
      circleList: circleList
    })
  },
  twinkle:function(){//设置一个定时器
    setInterval(function () {
      if (that.data.colorCircleFirst == '#FFDF2F') {
        that.setData({
          colorCircleFirst: '#FE4D32',
          colorCircleSecond: '#FFDF2F',
        })
      } else {
        that.setData({
          colorCircleFirst: '#FFDF2F',
          colorCircleSecond: '#FE4D32',
        })
      }
    }, 500)
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
  },
  getB64ByUrl: function (url) {
    const FileSystemManager = wx.getFileSystemManager();
    FileSystemManager.readFile({
      filePath: url,
      encoding: 'base64',
      success(res) {
        that.setData({
          imgB64: res.data
        });
      }
    })
  },
  
  foodTap: function (e) {
    const imgB64 = that.data.imgB64;
    if (!imgB64) {
      wx.showToast({
        title: '请上传图片',
      })
      return;
    };
    that.twinkle()
    that.getToken(function (token) {
      that.getResult(token);
    });
  },
  getToken: function (callback) {
    wx.request({
      url: 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=j8k8rz1EqXdPIfwjwQdEbwMG&client_secret=Tttbs1hLDQw0nKG6ecy5znFBGdv7sWGT',
      data: {},
      header: {
        'content-type': 'application/x-www-form-urlencoded'
      },
      success(res) {
        var token = res.data.access_token;
        
        return callback(token);
      }
    });
  },
  getResult: function (token) {
    wx.request({
      url: 'https://aip.baidubce.com/rest/2.0/image-classify/v2/dish?access_token=' + token,
      method: "POST",
      data: {
        image: that.data.imgB64,
        baike_num: 1,
        top_num: 1
      },
      header: {
        'content-type': 'application/x-www-form-urlencoded' // 默认值
      },
      success(res) {
        console.log(res.data.result[0].baike_info);
        var re;
        var value;
        try{
          value = wx.getStorageSync('热量');
          console.log(value[0].reliang);
          re = value[0].reliang-res.data.result[0].calorie;
          value[0].reliang = re;
          console.log(re);
        }catch(e){
          console.log(e);
        }
        wx.setStorageSync('热量', value);
        that.setData({
          dishName: res.data.result[0].name,
          calorie: res.data.result[0].calorie,
          probability: res.data.result[0].probability,
          reliang:re
        });
        // console.log('***************SUCCESS***********')
        // console.log('菜名：'+that.data.dishName);
        // console.log('卡路里：'+that.data.calorie);
        // console.log('置信度：'+that.data.probability);
        // console.log(res.data);
        wx.showModal({
          title: '菜品为：' +that.data.dishName,
          content: '热量为：' + that.data.calorie+'\n'+'是否查看详情?',
          success(res){
            if (res.confirm) {
              that.setData({ishow:true}) 
            }
            else{
              return
            }
          }
          
        })
       
      }
    });
  }
})