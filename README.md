# C++ Projektas
<!--![Imgur](https://imgur.com/TseEA4k.png)-->
![Imgur](https://imgur.com/TyNHcmc.png)
## Komanda: <!--a̶͗͆i̷̍͝ ̸͑͛ń̸̂e̷̿̎z̴̿̎ȉ̴nau-->
### Nariai:
- Tadas Riksas
<!--- Arnas Šniokaitis-->

![Imgur](https://imgur.com/TyNHcmc.png)
## Laiko fiksavimo programa
### Programos tikslas:
Tai būtų tokia programa, su kuria galima sekti PSP veiklą žymiai lengviau, 
negu susirašinėjant visus įvykius į word/excel dokumentą. Taip pat būtų 
galima sekti ir kitas veiklas, nesusiejusias su PSP, bet kurios reikalauja 
laiko fiksavimo. 

### Programos veikimo principas:
* vartotojas pasirenka veiklą
* Naudojantis `start`, `pause` ir `stop` mygtukais nustato veiklos būseną.
* Naudojantis `comment` sekcija apibudina, ką veikė.

### Programos funkcijos:
Visą surinktą informaciją būtų galima atvaiduoti keliais būdais:
* `CSV`, `excel` formatais.
* Grafikais ***(galimai bus neimplementuota dėl mažos komandos)***. 

### Programos struktūra:
<img src="https://imgur.com/1VFR1bb.png" width="800">

#### Frontend:
* Valdys įvestį, duomenų atvaizdavimą ir kitus interfeiso elementus.

#### Backend:
* Valdys duomenų saugojimą, apdorojimą ir kitus veiksmus, kurie nėra susiję su interfeisu.
* Pagrindinės funkcijos yra `startEvent`, `pauseEvent`, `stopEvent`, `comment`.


#### Naudojamos bibliotekos:
* `SFML` - grafiniam interfeisui kurti - [website](https://www.sfml-dev.org/).

#### Programos flowchart:

![Imgur](https://imgur.com/iYcAlUn.png)

### Programos vizija:
Kaip galėtų atrodyti programos interfeisas jeigu turėtume didelę komandą ir daug laiko:
![Imgur](https://imgur.com/kv7Vs5n.png)
Deja, tikėtina, kad galėsime sukurti tik tokį interfeisą:
![Imgur](https://imgur.com/5ERUZyN.png)

### Programos veikimo pavyzdys:
[![IMAGE ALT TEXT](https://imgur.com/f6U0fmw.png)](http://www.youtube.com/watch?v=FC6kq6OVsIQ "Video Title")




## Darbo apimties ataskaitos
Visos ataskaitos sudėtos į `Ataskaitos` katalogą.
