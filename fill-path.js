surface = new createXSurface(600, 600);
ctx = new Gepard(surface);

ctx.fillStyle = "#000";
ctx.fillRect(0, 0, 600, 600);

ctx.fillStyle = "#0f0";
ctx.setFillColor(0, 255, 0);
ctx.beginPath();
ctx.moveTo(300, 100);
ctx.lineTo(50, 230);
ctx.lineTo(380, 200);
ctx.closePath();
ctx.fill();

ctx.fillStyle = "#f00";
ctx.setFillColor(255, 0, 0);
ctx.setStrokeColor(0, 0, 255);
ctx.beginPath();
ctx.moveTo(100, 100);
ctx.lineTo(180, 200);
ctx.bezierCurveTo(400, 200, 40, 50, 300, 250);
ctx.closePath();
ctx.fill();
ctx.stroke();

image = ctx.getImageData(0, 0, surface.width, surface.height);
savePng(image, "temp/fill-path-js.png");
