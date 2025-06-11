# Códigos do projeto

Os códigos do projeto estão aqui. 
Aqui você encontra os códigos em python, do emulador de nuvem e rastreamento de onibus, bem como os códigos do emulador de ESP32, que foi feito no Wokwi.

Os arquivos são os seguintes:

### Emulador ESP32
- wokwi-project.txt => Informações de onde se pode acessar o projeto.
- diagram.json => Diagrama em json do dispositivo, como seus circuitos, sensores, etc. 
- sketch.ino => Código do dispositivo - código em C++ com as funcionalidades do dispositivo. 

### Emulador de nuvem em python
- main.py => Código em python, que emula um sistema em nuvem que rastreia a posição dos onibus. Até o momento, este código, apenas emula o rastreamento, não faz rastreamento de fato. Ele é apenas para prototipagem.

### API em python
- BD-Onibus => Essa api, feita em python, realiza o rastreio real dos veiculos, porém, como ela depende de api's estrangeiras, o rastreio é feito com veiculos que não são da cidade de Ribeirão Preto. Ela foi para testes de viabilidade de rastreio, porém, para fins de prototipagem e demonstração, o **emulador de nuvem em python** foi escolhido para ser o principal. Essa pasta está salva para fins de documentação e consultas.
