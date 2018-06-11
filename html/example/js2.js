/**
 * Created by Yuki on 2018/5/23.
 */
let can = document.getElementById('can');
let ctx = can.getContext('2d');
let ran = Math.random; //封装随机数
let circularLength = 1300;  //这里是生成的粒子的个数
can.width = window.innerWidth;
can.height = window.innerHeight;
let color = ['red', 'pink', 'lightgreen', 'yellow', 'skyblue'];
let circularArr = [];
let minR = 3; // 最小的粒子的半径
let maxR = 6;
let x = 10; //粒子的水平间隔
let y = 10; //粒子的垂直间隔
(function () {// 生成粒子的匿名函数
    let j = 0;
    for (let i = 0; i < circularLength; i++) {
        (i % 45 == 0) && (j++);
        circularArr.push({
            x: (x * (i % 45) * 5),
            y: (y * j * 5),
            r: (ran() * maxR ) + minR,
        });
    }
})()
let gradient = ctx.createLinearGradient(0, can.height, can.width, 0);
for (let j in color) {
    let co = color[j];
    gradient.addColorStop(j / color.length, co);
}
let anger = 0;

draw();
function draw() {
    anger++;
    ctx.clearRect(0, 0, can.width, can.height);
    let now = ~~(ran() * circularLength);
    let arr = [];
    for (let i = 0; i < circularArr.length; i++) {
        let c = circularArr[i];

        if (c.r > 1) {
            c.r -= .1;
        } else {
            c.r = (ran() * maxR) + minR
        }
        let long = Math.sqrt(Math.pow(c.x - can.width / 2, 2) + Math.pow(c.y - can.height / 2, 2));
        if (long < 2000) {
            ctx.globalAlpha = 0.02;
            ctx.beginPath();
            ctx.moveTo(can.width / 2, can.height / 2);
            ctx.save();
            ctx.translate(c.x, c.y);
            ctx.rotate((i * 3) - anger * .01);
            ctx.translate(-c.x / 3, -c.y / 3);
            ctx.lineTo(0, 0);
            ctx.strokeStyle = gradient;
            ctx.stroke();
            ctx.restore();
        }
        ctx.globalAlpha = 0.4;
        ctx.save();
        ctx.translate(c.x, c.y);
        ctx.rotate((i * 3) - anger * .01);
        ctx.translate(-c.x / 3, -c.y / 3);
        ctx.beginPath();
        ctx.arc(0, 0, c.r, 0, 2 * Math.PI);

        ctx.closePath();
        ctx.restore();
        ctx.fillStyle = gradient;
        ctx.fill();


    }

    requestAnimationFrame(draw)
}
window.onresize = function () {
    can.width = window.innerWidth;
    can.height = window.innerHeight;
}