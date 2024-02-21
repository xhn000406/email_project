const express = require("express");
const nodemailer = require('nodemailer');

const app =  express();
const sender = '你的qq邮箱@qq.com'
const rectiveer = '接受人的qq邮箱@qq.com'
const passWord  = '授权码'


const transporter = nodemailer.createTransport({
    //配置发送者的邮箱服务器和登录信息
    service:'qq',//163、qq等
    auth:{
        user:sender,//邮箱
        pass:passWord //授权码
    }
});

var mailOptions = {
    from:sender ,//'"邮件显示名" <xxx@qq.com>',
    to:rectiveer,//接受者 //'xxx@qq.com,xxx@163.com'支持多个邮件
    subject:'火警警报',//主题名
    text:'你家要被烧了',//文本
    html:`<h2>您好</h2>`,//内容,
}



app.get('/demo',(req,res)=>{
    transporter.sendMail(mailOptions ,(err,info)=>{
        if(err) return console.log(err);
        if(info){
            console.log("发送成功")
            res.sendStatus(200);
        }
    })
   
})




app.listen(9090,()=>{
  console.log("开始监听")
})