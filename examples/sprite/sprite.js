/* Copyright (C) 2020, Gepard Graphics
 * Copyright (C) 2020, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds) {
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
for (i = 0; !surface.hasToQuit() && i < 21; i++) {
    sx = i % numOfSprites * spW;
    gepard.fillRect(0, 0, surface.width, surface.height);
    dx = i * bgStep % surface.width;
    gepard.drawImage(background, 0, 0, background.width, background.height, surface.width - dx, 0, surface.width, surface.height);
    gepard.drawImage(background, 0, 0, background.width, background.height, -dx, 0, surface.width, surface.height);
    gepard.drawImage(image, sx, sy, sw, sh, 250, dy, dw, dh);
    gepard.finish();
    sleep(64);
    if (!(i % 5)){
        var frame = gepard.getImageData(0, 0, surface.width, surface.height);
        savePng(frame, "temp/frame"+i+".png");
    }
}
