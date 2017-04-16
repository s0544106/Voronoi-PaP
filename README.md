# Voronoi-PaP
Semesterprojekt des Kurses Parallele Architekturen und Prozesse an der HTW Berlin

Dies ist ein simples Projekt zum Erstellen von Voronoi-Diagrammen. Es wurde erstellt um die Parallelisierung mit Hilfe von OpenMP kennenzulernen.
Die notwendigen Berechnungen werden hier einmal sequentiell und einmal parallel ausgeführt. Beide Ablaufzeiten werden gemessen und ausgegeben, bevor eine grafische Darstellung des Diagrams folgt.

Dieses Projekt wurde unter Arch Linux in der Programmiersprache C erstellt.

Installation
----------------
Dieses Programm beötigt ausser den Standartbibliotheken noch die <GL/glut.h>.
Hierfür ist es notwendig, dass OpenGL auf dem System installiert ist.

Anschliessend kann das Programm als zip geladen, oder mit folgendem Befehl heruntergeladen werden

git clone https://github.com/s0544106/Voronoi-PaP.git

Um den Voronoi-Generator starten zu können, muss das Programm noch mit dem "make" Befehl installiert werden.

Anwendung
----------------
Der Voronoi-Generator liest bestimmte Werte aus einer beiliegenden Textdatei und wird daher wie folgt gestartet:

./voronoi coordinates900

Nun kann den Anweisungen auf dem Bildschirm gefolgt, und Voronoi-Diagramme erstellt werden

