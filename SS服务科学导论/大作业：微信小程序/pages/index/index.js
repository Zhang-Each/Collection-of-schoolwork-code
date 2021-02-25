//index.js
//获取应用实例
const app = getApp()
var util = require('../../utils/util.js');  
Page({
  data: {
    total_circles: 0,
    title: "每周睡眠记录",
    motoo: "总有人黑着眼眶熬着夜。",
    userInfo: {},
    beginTime:'23:00',
    endTime: '6:30',
    signinPic:'../../images/clock.png',
  },
  //修改签到时间
  updateTime: function () {
    wx.navigateTo({
      url: '../time/time'
    })
  },

  bindCircleInput: function (e) {
    this.setData({
      total_circles: this.data.total_circles + parseInt(e.detail.value)
    })
  },

  //签到
  //自定义toast
  //  toastShow: function (str, icon) {
  //   var _this = this;
  //   _this.setData({
  //     isShow: true,
  //     txt: str,
  //     icon: icon
  //   });
  //   setTimeout(function () {    //toast消失
  //     _this.setData({
  //       isShow: false
  //     });
  //   }, 1500);
  // },
  // onLoad: function () {
  //   let last_signDate = wx.getStorageSync('last_signDate')
  //   if (last_signDate!=''){
  //     //获取今天日期
  //     let nowDate = util.formatDate(new Date());
  //     //如果今天已经签过到了
  //     if (nowDate == last_signDate){
  //       this.setData({
  //         signinPic: '../../images/clock.png'
  //       })
  //     }
  //   }
  //   //设置签到时间
  //   let temp = wx.getStorageSync('beginTime')
  //   let beginTime = temp == '' ? '21:00' : temp
  //   temp = wx.getStorageSync('endTime')
  //   let endTime = temp == '' ? '24:00' : temp
  //   this.setData({
  //     beginTime: beginTime,
  //     endTime: endTime,
  //   })
  //   //设置签到记录
  //   let temp_record = wx.getStorageSync('sign_days')
  //   let sign_days = temp_record == '' ? 0 : temp_record
  //   temp_record = wx.getStorageSync('running_days')
  //   let running_days = temp_record == '' ? 0 : temp_record
  //   temp_record = wx.getStorageSync('long_running_days')
  //   let long_running_days = temp_record == '' ? 0 : temp_record
  //   this.setData({
  //     sign_days: sign_days,
  //     running_days: running_days,
  //     long_running_days: long_running_days,
  //   })
    
  // },
  // onShow: function () {
  //   let last_signDate = wx.getStorageSync('last_signDate')
  //   if (last_signDate != '') {
  //     //获取今天日期
  //     let nowDate = util.formatDate(new Date());
  //     //如果今天已经签过到了
  //     if (nowDate == last_signDate) {
  //       this.setData({
  //         signinPic: '../../images/clock.png'
  //       })
  //     }
  //   }
  //   //设置签到时间
  //   let temp = wx.getStorageSync('beginTime')
  //   let beginTime = temp == '' ? '21:00' : temp
  //   temp = wx.getStorageSync('endTime')
  //   let endTime = temp == '' ? '24:00' : temp
  //   this.setData({
  //     beginTime: beginTime,
  //     endTime: endTime,
  //   })
  //   //设置签到记录
  //   let temp_record = wx.getStorageSync('sign_days')
  //   let sign_days = temp_record == '' ? 0 : temp_record
  //   temp_record = wx.getStorageSync('running_days')
  //   let running_days = temp_record == '' ? 0 : temp_record
  //   temp_record = wx.getStorageSync('long_running_days')
  //   let long_running_days = temp_record == '' ? 0 : temp_record
  //   this.setData({
  //     sign_days: sign_days,
  //     running_days: running_days,
  //     long_running_days: long_running_days,
  //   })
  // },
  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function (option) {
    console.log(option)
    /*
    return {
      title: '自定义转发标题',
      path: '/page/index/index'
    }
    */

  }
})
