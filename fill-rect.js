print("start");

surface = new createXSurface(600, 600);
gepard = new Gepard(surface);

gepard.setFillColor(128, 102, 26, 0.05);
gepard.fillRect(50, 50, 500, 500);

gepard.setFillColor(0, 204, 77, 0.8);
gepard.fillRect(100, 100, 80, 400);

gepard.setFillColor(0, 0, 26, 0.8);
gepard.fillRect(100, 420, 280, 80);

gepard.setFillColor(77, 0, 179);
gepard.fillRect(180, 100, 200, 80);

gepard.setFillColor(77, 179, 51);
gepard.fillRect(380, 80, 80, 130);

// isn't working yet
//gepard.fillStyle = "#af5f4f";
gepard.setFillColor(175, 95, 79);
gepard.fillRect(380, 380, 80, 130);

gepard.setFillColor(220, 180, 40);
gepard.fillRect(330, 320, 160, 60);
print("hmm");
while(!surface.hasToQuit()) {}
print("quit");