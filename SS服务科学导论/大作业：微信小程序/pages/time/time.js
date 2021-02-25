// pages/time/time.js
const app = getApp()
var util = require('../../utils/util.js');  
//设置显示时间
let temp = wx.getStorageSync('beginTime')
let beginTime = temp == '' ? '23:00' : temp
temp = wx.getStorageSync('endTime')
let endTime = temp == '' ? '6:30' : temp
//初始化picker,并计算picker选择默认选中的时间
const sel_beginTime = []
const sel_endTime = []
let begin_index = 0
let end_index = 0
for (let i = 19; i <= 23; i++) {
  sel_beginTime.push(i+':00')
  sel_beginTime.push(i + ':30')
  if (beginTime == (i + ':00')){
    begin_index = (i-19)*2
  }
  if (beginTime == (i + ':30')) {
    begin_index = (i-19)*2-1
  }
}
for (let i = 4; i <= 7; i++) {
  sel_endTime.push(i + ':00')
  sel_endTime.push(i + ':30')
  if (endTime == (i + ':00')){
    end_index = (i-4)*2
  }
  if (endTime == (i + ':00')) {
    end_index = (i - 4) * 2 - 1
  }
}

Page({
  /**
   * 页面的初始数据
   */
  data: {
    sel_beginTime: sel_beginTime,
    sel_endTime: sel_endTime,
    begin_index: begin_index,
    end_index: end_index,
    beginTime: beginTime,
    endTime: endTime,
    buttonDis:false,
    // beginTime: sel_beginTime[begin_index],
    // endTime: sel_endTime[end_index],  
  },
  
  showTarget:function(){
    wx.showToast({
      title: '修改成功！',
    })
} ,
  bindBeginTimeChange:function(e){
  //  console.log(e.detail.value + "," + this.data.end_index)
    let right_index = e.detail.value
    this.setData({
      beginTime: sel_beginTime[right_index],
      begin_index: right_index
    })
  //  console.log(sel_beginTime)
  //  console.log(this.data.begin_index + "," + this.data.end_index)
  //  console.log(this.data.beginTime + "," + this.data.endTime)
  },
  bindEndTimeChange: function (e) {
    let right_index = e.detail.value
    this.setData({
      endTime: sel_endTime[right_index],
      end_index: right_index
    })
    // console.log(this.data.begin_index + "," + this.data.end_index)
    // console.log(this.data.beginTime + "," + this.data.endTime)
  },
  bindSetTime: function (e) {
    wx.setStorage({ key: 'beginTime', data: beginTime })
    wx.setStorage({ key: 'endTime', data: endTime })
    wx.navigateTo({
      url: '../index/index'
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    let beginTime = wx.getStorageSync("beginTime")
    let endTime = wx.getStorageSync("endTime")
    if(beginTime!=''){
      this.setData({
        beginTime: beginTime,
        endTime: endTime
      })
    }
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
      this.setData({
        buttonDis:false
      })
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
  
  },
  test:function(e){
    console.log(e)
  }
})