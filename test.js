surface = new createXSurface(600, 800);

print(surface)
print(surface.width + " " + surface.height);

gepard = new Gepard(surface);
gepard.fillRect();
gepard.setFillColor(255, 255, 20);
gepard.fillRect(4, 4, 100, 100);
gepard.setFillColor(0, 0, 128, 0.5);
gepard.fillRect(10, 10, 400, 500);

while(!surface.hasToQuit()) {}
