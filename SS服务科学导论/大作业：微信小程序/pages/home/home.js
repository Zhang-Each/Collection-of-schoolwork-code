var util = require('../../utils/util.js');  
const app = getApp();
Page({
  data: {
    //测试授权结果
    ID: "请授权登录",
    //判断小程序的API，回调，参数，组件等是否在当前版本可用。
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    beginTime: '23:00',
    endTime: '6:30',
    currenttime: 0,
    bg: 'day'
  },
  onLoad: function () {
    let time = new Date()
    let currenttime = time.getHours()
    let bg = (currenttime >= 6 && currenttime < 18) ? 'day':'night'
    let that = this
    // 查看是否授权过
    wx.getSetting({
      success: function (res) {
        if (res.authSetting['scope.userInfo']) {
          let userInfo = wx.getStorageSync('userInfo')
          let userid = wx.getStorageSync('userid')
          //签到时间
          let temp = wx.getStorageSync('beginTime')
          let beginTime = temp == '' ? '23:00' : temp
          temp = wx.getStorageSync('endTime')
          let endTime = temp == '' ? '6:30' : temp
          that.setData({
            userInfo: userInfo,
            ID:"ID:"+userid,
            beginTime: beginTime,
            endTime: endTime,
            currenttime: currenttime,
            bg: bg
          })
          //console.log("用户已经授权过")
        }else{
          //console.log("用户没有授权过/授权信息已不存在");
        }
      }
    })
  },
  setTime: function (token) {
    let that = this
   // console.log(token)
    //正在判断是否设置过时间
    wx.request({
      url: app.globalData.domain+'/GetTimeServlet',
      method: "POST",
      data: {
        token: token
      },
      header: {
        //设置参数内容类型为x-www-form-urlencoded
        'content-type': 'application/x-www-form-urlencoded',
        'Accept': 'application/json'
      },
      success: function (result) {
       // console.log(result)
       // console.log("beginTime:" + result.data.beginTime)
        //如果没设置过
        if (result.data.last_update==''){
         // console.log("用户没设置过")
          wx.navigateTo({
            url: '../time/time'
          })
        }else{
         // console.log("用户设置过")
          wx.setStorageSync('beginTime', result.data.beginTime)
          wx.setStorageSync('endTime', result.data.endTime)
          wx.setStorageSync('last_update', result.data.last_update)
          that.setData({
            beginTime: result.data.beginTime,
            endTime: result.data.endTime
          })
        }
      }
    })
  },
  onShow:function(){
    let temp = wx.getStorageSync('beginTime')
    let beginTime = temp == '' ? '21:00' : temp
    temp = wx.getStorageSync('endTime')
    let endTime = temp == '' ? '24:00' : temp
    this.setData({
      beginTime: beginTime,
      endTime: endTime
    })

  },
  bindFunc: function (e) {
    //console.log(e)
    let formid = e.detail.formId
    //console.log(formid)
    util.sendFormID(formid)
  },
bindToUpdateTime:function(){
    wx.navigateTo({
      url: '../time/time'
    })
  },
bindSignRecord:function(){
  wx.navigateTo({
    url: '../signRecord/signRecord'
  })
},
bindToCalRecord: function () {
    wx.navigateTo({
      url: '../calendar/calendar'
    })
},
bindToAdmire:function(){
  wx.navigateTo({
    url: '../index/index'
  })
},
bindToAbout: function () {
  wx.navigateTo({
    url: '../indexm/indexm'
  })
},
 /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function (option) {
  console.log(option)
}
})