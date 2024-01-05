-----------------------------------------------------------NFC-tag-editor-----------------------------------------------------
                                                                        
Progetto riguardante un piccolo dispositivo che grazie a Arduino nano e il lettore RC522 permette di modificare facilmente e in modo ripetuto tag nfc

![image](https://github.com/joel00007/NFC-tag-editor/assets/148422777/7cdaf10d-7db8-4cf4-9df7-e7ba50bbb3bd)


![image](https://github.com/joel00007/NFC-tag-editor/assets/148422777/c4964f3a-9a79-42b3-ba47-4f4b195457c4)





Salve.
È da un po' di tempo che penso di realizzare questo piccolo, ma divertente progetto. Ho iniziato con delle prove utilizzando un Arduino Mega, alcuni 
LED e un piccolo schermo OLED. Tutto funzionava bene, ma ha perso di significato a causa delle dimensioni non accettabili.
Quindi, eccomi qua: ho acquistato un nuovo lettore e un microcontrollore Arduino Nano. Ho disegnato l'intero case in 3D per ottenere un risultato
esteticamente gradevole.
Lo scopo di questo progetto è creare un oggetto tascabile e esteticamente piacevole per modificare facilmente e velocemente i tag NFC. L'idea mi
è venuta quando ho installato delle serrature smart con tecnologia a 13,56 MHz e ho dovuto creare più tag, modificando gli UID di quelli acquistati 
da terze parti.

![EXPLORER v12](https://github.com/joel00007/NFC-tag-editor/assets/148422777/1d4dbb2b-0c5c-405e-81f9-f5b5c20eccd8)

![EXPLORER v31](https://github.com/joel00007/NFC-tag-editor/assets/148422777/5e7c62c9-ac0c-4f9d-84fc-e4d026ee00ad)
Il collegamento del lettore e del bottone è molto semplice, basta aggiungere interruzione al collegamento del polo positivo:

![immagine_2024-01-04_185859360-removebg-preview](https://github.com/joel00007/NFC-tag-editor/assets/148422777/7c64ebbe-a12a-41bc-b72d-63172c51675b)


Invece il collegamento del lettore rc522 a arduino nano è questo:


![immagine_2024-01-04_185955364-removebg-preview (1)](https://github.com/joel00007/NFC-tag-editor/assets/148422777/a9834feb-2f4c-4c8e-9805-4778571e125d)

Ho poi scelto di aggiungere un piccolo led di diametro 5mm al interno del case, collegato al pin D8 e al GND


Tutto l'occorrente l'ho acquistato qua:
- Arduino nano e RC522: https://www.amazon.it/gp/product/B07JLBGYQ6/ref=ox_sc_act_title_5?smid=A1X7QLRQH87QA3&th=1
- Porta batteria 9v: https://www.amazon.it/gp/product/B0823W1MX7/ref=ox_sc_act_title_2?smid=A2ZY4SNMU91J2Q&th=1
  Oppure: https://www.amazon.it/gp/product/B095VVDJDL/ref=sw_img_1?smid=ASLRAS85RTYN3&psc=1
- Bottone meccanico: https://www.amazon.it/gp/product/B07L74MMG8/ref=sw_img_1?smid=A12HG9LT85UKFZ&th=1
