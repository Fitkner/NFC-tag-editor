-----------------------------------------------------------NFC-tag-editor-----------------------------------------------------
                                                                        
Progetto riguardante un piccolo dispositivo che grazie a Arduino nano e il lettore RC522 permette di modificare facilmente e in modo ripetuto tag nfc
![EXPLORER v12](https://github.com/joel00007/NFC-tag-editor/assets/148422777/1d4dbb2b-0c5c-405e-81f9-f5b5c20eccd8)


Salve.
È da un po' di tempo che penso di realizzare questo piccolo, ma divertente progetto. Ho iniziato con delle prove utilizzando un Arduino Mega, alcuni 
LED e un piccolo schermo OLED. Tutto funzionava bene, ma ha perso di significato a causa delle dimensioni non accettabili.
Quindi, eccomi qua: ho acquistato un nuovo lettore e un microcontrollore Arduino Nano. Ho disegnato l'intero case in 3D per ottenere un risultato
esteticamente gradevole.
Lo scopo di questo progetto è creare un oggetto tascabile e esteticamente piacevole per modificare facilmente e velocemente i tag NFC. L'idea mi
è venuta quando ho installato delle serrature smart con tecnologia a 13,56 MHz e ho dovuto creare più tag, modificando gli UID di quelli acquistati 
da terze parti.

![image](https://github.com/joel00007/NFC-tag-editor/assets/148422777/e7dd7593-5063-4b13-8d43-250e026398b6)

![EXPLORER v31](https://github.com/joel00007/NFC-tag-editor/assets/148422777/5e7c62c9-ac0c-4f9d-84fc-e4d026ee00ad)
Il collegamento del lettore e del bottone è molto semplice, basta aggiungere un piccolo bottone al collegamento del polo positivo:

![immagine_2024-01-04_185859360-removebg-preview](https://github.com/joel00007/NFC-tag-editor/assets/148422777/7c64ebbe-a12a-41bc-b72d-63172c51675b)


Invece il collegamento del lettore rc522 a arduino nano è questo:


![immagine_2024-01-04_185955364-removebg-preview (1)](https://github.com/joel00007/NFC-tag-editor/assets/148422777/a9834feb-2f4c-4c8e-9805-4778571e125d)



Tutto l'occorrente l'ho acquistato qua:
- Arduino nano e RC522: https://www.amazon.it/gp/product/B07JLBGYQ6/ref=ox_sc_act_title_5?smid=A1X7QLRQH87QA3&th=1
- Porta batteria 9v: https://www.amazon.it/gp/product/B0823W1MX7/ref=ox_sc_act_title_2?smid=A2ZY4SNMU91J2Q&th=1
- Bottone meccanico: https://www.amazon.it/gp/product/B07L74MMG8/ref=sw_img_1?smid=A12HG9LT85UKFZ&th=1
