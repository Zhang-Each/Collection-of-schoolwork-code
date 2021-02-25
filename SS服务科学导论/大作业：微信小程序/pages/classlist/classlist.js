// pages/calendar/calendar.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    colorArrays: [ "#85B8CF", "#90C652", "#D8AA5A", "#FC9F9D", "#0A9A84", "#61BC69", "#12AEF3", "#E29AAD"],
    classlist: [
      { "day": 1, "start": 1, "long": 2, "name": "信息安全原理" },
      { "day": 1, "start": 7, "long": 2, "name": "服务科学导论" },
      { "day": 2, "start": 10, "long": 2,"name":"集邮与文化"},
      { "day": 2, "start": 1, "long": 4, "name": "服务科学导论" },
      { "day": 3, "start": 1, "long": 2, "name": "面向对象程序设计" },
      { "day": 3, "start": 3, "long": 3, "name": "高级数据结构与算法分析" },
      { "day": 3, "start": 7, "long": 2, "name": "计算机系统原理" },
      { "day": 4, "start": 3, "long": 3, "name": "数据库系统" },
      { "day": 4, "start": 7, "long": 2, "name": "信息安全原理" },
      { "day": 5, "start": 3, "long": 2, "name": "计算机系统原理" },
      { "day": 7, "start": 1, "long": 10, "name": "DDL" },
    ]
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },
  showCardView: function(){
    wx.showToast({
      title: '功能仍在开发中！',
    })
  }
})