/* Copyright (C) 2019, Gepard Graphics
 * Copyright (C) 2019, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
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

surface = new createXSurface(600, 600);
gepard = new Gepard(surface);

gepard.setFillColor(255, 102, 26, 0.05);
gepard.fillRect(50, 50, 500, 500);

gepard.setFillColor(0, 204, 77, 0.8);
gepard.fillRect(100, 100, 80, 400);

gepard.setFillColor(0, 0, 26, 0.8);
gepard.fillRect(100, 420, 280, 80);

gepard.fillStyle = "#4d00b3";
gepard.fillRect(180, 100, 200, 80);

gepard.setFillColor(77, 179, 51);
gepard.fillRect(380, 80, 80, 130);

gepard.fillStyle = "#af5f4f";
gepard.fillRect(380, 380, 80, 130);

gepard.setFillColor(220, 180, 40);
gepard.fillRect(330, 320, 160, 60);
while(!surface.hasToQuit()) {}

image = gepard.getImageData(0, 0, surface.width, surface.height);
savePng(image, "temp/fill-rect-js.png");

try {
    fakeGepard = new Object();
    fakeGepard.fillRect = gepard.fillRect;
    fakeGepard.fillRect(10, 10, 40, 40);
} catch(err) {
    print(err);
}
