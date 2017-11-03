module.exports = function(app){

  if (!app) throw new Error('Must provide express instance.');

  var fs = require('fs')
  var multer  = require('multer');
  var path = require("path");
  var express = require('express')

  Date.prototype.Format = function (fmt) { //author: meizz
    var o = {
      "M+": this.getMonth() + 1, //月份
      "d+": this.getDate(), //日
      "h+": this.getHours(), //小时
      "m+": this.getMinutes(), //分
      "s+": this.getSeconds(), //秒
      "q+": Math.floor((this.getMonth() + 3) / 3), //季度
      "S": this.getMilliseconds() //毫秒
    };
    if (/(y+)/.test(fmt)) fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
    for (var k in o)
      if (new RegExp("(" + k + ")").test(fmt)) fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
    return fmt;
  };



  var storage = multer.diskStorage({
    destination: function (req, file, cb) {

      var date = (new Date()).Format("yyyy-MM-dd");
      var path = 'uploads/'+ date;

      if (!fs.existsSync(path)) {

        fs.mkdir(path,0755, function (err) {
          if (err) throw err;
        });

      }
      cb(null, 'uploads/'+ (new Date()).Format("yyyy-MM-dd"))
    },

    filename: function (req, file, cb) {

      //
      console.log('file', file);
      cb(null, file.fieldname + '-' + Date.now()+path.extname(file.originalname))
    }
  });

  var upload = multer({storage: storage});



  app.post('/img/upload', upload.array('photos', 12), function (req, res, next) {

    try {
      console.log(req.body.myfile);
      console.log(req.files);
      res.json(req.files[0].path);
    } catch (e) {
      console.log(e);
    }
  });


  app.use('/uploads', express.static('uploads'));

  return app;

};
