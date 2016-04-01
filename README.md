*Dieser Code ist Teil von und entwickelt für [Citybound](http://cityboundsim.com).
Irgendwann könnte er stabil und allgemein benutzbar werden!!*

# whiteboard

## Einfache graphische Konsolenausgabe

Stell dir vor, du könntest auf der Standardausgabe einfach eine kleine Zeichnung ausgeben!
*whiteboard* macht dies möglich!

Schicke einfach speziell formatierte Zeichnungskommandos über die Standardausgabe und z.B. eine Röhre in whiteboard hinein.

**zeichnung.txt**
```
Whiteboard: ----
Whiteboard: arc 0.25 0.25 1 0 0.25 0.75
Whiteboard: arc 0.25 0.75 -1 0 0.25 0.25
Whiteboard: arc 0.5 0.25 1 0 0.5 0.75
Whiteboard: arc 0.5 0.75 -1 0 0.5 0.25
Whiteboard: color 0 0 0 64
Whiteboard: line 0.25 0.5 0.4 0.759808
Whiteboard: line 0.25 0.5 0.4 0.240192
Whiteboard: line 0.5 0.5 0.35 0.759808
Whiteboard: line 0.5 0.5 0.35 0.240192
Whiteboard: color 255 0 0 255
Whiteboard: dot 0.375 0.716506
Whiteboard: dot 0.375 0.283494
```
und dann:

```
whiteboard < zeichnung.txt
```

zeigt folgendes Fenster an:

![](http://i.imgur.com/alwAWdY.png)

## Beispielanwendungen

[compass](https://github.com/citybound/compass), die Geometriebibliothek von Citybound benutzt whiteboard um Einheitentests graphisch zu veranschaulichen. Hier wurden auch ein paar Hilsfunktionen geschrieben, um z.B. einfach eine Gerade oder einen Kreis auf das whiteboard zu zeichnen.

## Lizenz

MIT, siehe [LICENSE.md](LICENSE.md) für Details.
