function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}

surface = new createXSurface(750, 500);
gepard = new Gepard(surface);
image = loadPng("sprite.png");
background = loadPng("plx-4.png");
gepard.setPresentModeOnDemand();
gepard.setFillColor(255, 255, 255, 1.0);
numOfSprites = 8;
bgStep = 10;
spW = 84;   // sprite width
spH = 132;  // sprite height
sx = 0;
sy = 0;
sw = spW;
sh = spH;
dx = 0;
dy = 318;
dw = sw;
dh = sh;
for(i = 0; !surface.hasToQuit() && i < 21; i++) {
    sx = i % numOfSprites * spW;
    gepard.fillRect(0, 0, surface.width, surface.height);
    dx = i * bgStep % surface.width;
    gepard.drawImage(background, 0, 0, background.width, background.height, surface.width - dx, 0, surface.width, surface.height);
    gepard.drawImage(background, 0, 0, background.width, background.height, -dx, 0, surface.width, surface.height);
    gepard.drawImage(image, sx, sy, sw, sh, 250, dy, dw, dh);
    gepard.finish();
    sleep(64);
    if (!(i%5)){
        var frame = gepard.getImageData(0, 0, surface.width, surface.height);
        savePng(frame, "temp/frame"+i+".png");
    }
}
