Projet openGL des ING13
=======================

version de Gabin Schittek, Philémon Pensier, et Alban Kraus

Ce document est destiné aux ING14 qui souhaiteraient s'inspirer de
notre projet. Je vous conseille de commencer par le compiler, ce qui
vous assurera que vous disposez des bonnes bibliothèques. Si le code
vous paraît incompréhensible, essayez de consulter le
[rapport](doc/rapport.pdf) qui contient plus de détails sur la manière
dont nous avons codé.

Tous les codes et documents de ce dossier sont sous license LGPL, ce
qui vous permet de les réutiliser, en y apportant éventuellement des
modifications, dans n'importe quel but, y compris commercial, sous une
license quelconque, à condition de citer le nom des auteurs originaux.




Présentation
============


Environnement
-------------

Nous utilisons [`qmake`](http://www.qt.io/download-open-source/) et
GNU `make` ([site officiel](https://www.gnu.org/software/make/)) pour
ordonner la compilation de notre programme. Notez que les
bibliothèques de Qt ne sont pas requises, seulement qmake.

Nous utilisons les bibliothèques :
[OpenGL, GLU](https://www.opengl.org/wiki/Getting_started), et
[glut](http://freeglut.sourceforge.net/).

Le rapport est rédigé en LaTeX. Pour plus de détail, vous pourrez vous
reporter au [Wikibook](https://fr.wikibooks.org/wiki/LaTeX).

**Attention** une valeur est *inscrite en dur* dans le code : le chemin
  vers le graphe. Vous devrez l'adapter à votre environnement. Oui, je
  sais, c'est mal foutu, nous étions jeunes et inexpérimentés.


Sujet
-----

Notre projet avait pour objectif de faire avancer un puis plusieurs
trains sur un graphe. Avec plusieurs trains, une gestion des
collisions était indispensable.


Arborescence
------------

`data/`     : contient le graphe sur lequel les trains vont circuler ;

`demo/`     : non-utilisé ;

`doc/`      : contient le rapport ;

`src/`      : contient les sources ;

`src/_api/` : contient les classes fournies pour exploiter le graphe.



Conclusion
==========

Pour toute question sur la compilation avec qmake, voire la
configuration de Qt Creator (ou à la rigueur Code::Blocks), n'hésitez
pas à contacter les auteurs.

Bon courage à tous !


+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+  
© Alban Kraus, 16 décembre 2015
  alban.kraus@ensg.eu
