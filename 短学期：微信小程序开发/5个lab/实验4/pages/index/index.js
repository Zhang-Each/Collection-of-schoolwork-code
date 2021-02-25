//index.js
//获取应用实例
const app = getApp()

Page({
  data: {
    result: "0",
    idb: "back",
    idc: "clear",
    idadd: "＋",
    idj: "－",
    idx: "×",
    iddiv: "÷",
    ide: "＝",
    idm: "%",
    id9: "9",
    id8: "8",
    id7: "7",
    id6: "6",
    id5: "5",
    id4: "4",
    id3: "3",
    id2: "2",
    id1: "1",
    id0: "0",
    idd: ".",
    calculator: { "＋": "+", "－": "-", "×": "*", "÷": "/", ".": "." },
    nextcal: false,
    arr: [],
    logs: []
  },

  clickandcal: function (event) {
    var id = event.target.id;
    if (id == this.data.idb) {
      var data = this.data.result;
      if (data == "0") {
        return;
      }
      data = data.substring(0, data.length - 1);
      if (data==""||data=="－") {
        data = 0;
      }
      this.setData({ "result": data });
      this.data.arr.pop();
    } else if (id==this.data.idc) {
      this.setData({ "result": "0" });
      this.data.arr.length = 0;
    } else if (id==this.data.idt) {
      var data = this.data.result;
      if (data=="0") {
        return;
      }
      var firstWord = data.charAt(0);
      if (data == "－") {
        data = data.substr(1);
        this.data.arr.shift();
      } else {
        data = "－" + data;
        this.data.arr.unshift("－");
      }
      this.setData({ "result": data });
    } else if (id == this.data.ide) {
      var data = this.data.result;
      if (data == "0") {
        return;
      }
      var lastWord=data.charAt(data.length);
      if (isNaN(lastWord)) {
        return;
      }
      var num="";
      var lastOperator = "";
      var arr=this.data.arr;
      var optarr=[];
      for (var i in arr) {
        if (isNaN(arr[i])==false||arr[i]==this.data.idd||arr[i]==this.data.idt) {
          num=num+arr[i];
        } else {
          lastOperator=arr[i];
          optarr.push(num);
          optarr.push(arr[i]);
          num = "";
        }
      }
      optarr.push(Number(num));
      var re = Number(optarr[0]) * 1.0;
      console.log(re);
      for (var i = 1; i < optarr.length; i++) {
        if (isNaN(optarr[i])) {
          if (optarr[1] == this.data.idadd) {
            re = re + Number(optarr[i + 1]);
          } else if (optarr[1] == this.data.idj) {
            re = re - Number(optarr[i + 1]);
          } else if (optarr[1] == this.data.idx) {
            re = re * Number(optarr[i + 1]);
            re = re.toFixed(2);
          } else if (optarr[1] == this.data.iddiv) {
            re = re / Number(optarr[i + 1]);
            re = re.toFixed(2);
          } else if (optarr[1] == this.data.idm) {
            re = parseInt(re % Number(optarr[i + 1]));
          }
        }
      }
      this.data.logs.push(data + '=' + re);
      wx.setStorageSync("calclogs", this.data.logs);
      this.data.arr.length = 0;
      this.data.arr.push(re);
      this.setData({ "result": re + "" });
    }
    else {
      if (this.data.calculator[id]) {
        if (this.data.nextcal || this.data.result == "0") {
          return;
        }
      }
      var x = this.data.result;
      var y;
      if (x == 0) {
        y = id;
      } else {
        y = x + id;
      }
      this.setData({ "result": y });
      this.data.arr.push(id);
      if (this.data.calculator[id]) {
        this.setData({ "nextcal": true });
      } else {
        this.setData({ "nextcal": false });
      }
    }
  },
})