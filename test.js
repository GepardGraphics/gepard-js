surface = new createXSurface(600, 800);

print(surface.width + " " + surface.height);

gepard = new Gepard(surface);

print("createImageData");
im = gepard.createImageData(400, 400);
print(im.width + " " + im.height);

image = loadPng("/home/kkristof/work/gepard/fill-rect.png");
print(image.width + " " + image.height);
im2 = gepard.createImageData(image);
print("image2: " + im2.width + " " + im2.height);
gepard.rotate(0.3);
gepard.translate(100, 100);
gepard.drawImage(image, 0, 0, 100, 400);
gepard.putImageData(image, 100, 200);

image3 = gepard.getImageData(0, 0, 400, 400);
savePng(image3, "temp/testDrawImage.png");
savePng(image,  "temp/test.png");
