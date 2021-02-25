
//绘图方式实现白云飘动
function drawAnimaCloud() {
  var cloud1= '../res/cloud_one.png';
  var cloud2= '../res/cloud_two.png';
  var cloud3= '../res/cloud_three.png';
  var that = this;
  var deviceWidth;
  wx.getSystemInfo({
    success: function (res) {
      deviceWidth = res.windowWidth;
    },
  })
  // 使用 wx.createContext 获取绘图上下文 context
  var context = wx.createCanvasContext('cloudCanvas')
  var i = 0;//白云1速度基数
  var j = 0;//白芸2速度基数
  var k = 0;//白芸3速度基数

  setInterval(function () {
    if (i > deviceWidth) {
      i = -deviceWidth;
    }

    if (j > deviceWidth) {
      j = -deviceWidth;
    }
    if (k > deviceWidth) {
      k = -deviceWidth;
    }
    context.drawImage(cloud1, i - deviceWidth, 0, deviceWidth, 150)
    context.drawImage(cloud1, i, 0, deviceWidth, 150)
    context.drawImage(cloud2, j, 5, deviceWidth, 150)
    context.drawImage(cloud3, k, 10, deviceWidth, 150)
    context.draw()
    i += 0.5;
    j += 1;
    k += 1.25;
  }, 50)
}

//暴露函数，供外部调用
module.exports = {
  drawAnimaCloud: drawAnimaCloud
};