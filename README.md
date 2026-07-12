# ESP8266 ile IR Kumanda Klonlama

ESP8266 kullanarak kızılötesi (IR) kumanda sinyallerini okuyup, bir IR LED devresiyle yeniden gönderme (klonlama) projesi. NEC ve LG protokollerini destekler, web tabanlı bir arayüz (captive portal) üzerinden çalışır.

## Özellikler

- IR alıcı modül ile kumanda sinyallerini okuma ve hex koda çözme
- NEC ve LG protokolü desteği
- IR LED + transistör devresi ile sinyal yeniden gönderme
- ESP8266 üzerinde Access Point (AP) modu ve captive portal ile tarayıcı üzerinden kontrol
- Harici bir kumandaya veya WiFi ağına bağımlı olmadan çalışma

## Kullanılan Donanım

| Bileşen | Açıklama |
|---|---|
| ESP8266 (NodeMCU) | Ana denetleyici |
| IR alıcı modül | Kumanda sinyallerini okumak için |
| Kızılötesi (IR) LED | Sinyali yeniden göndermek için |
| BC337 transistör | IR LED sürücü devresi |
| Direnç | Akım sınırlama (transistör base ve LED için, devrenize göre hesaplayın) |
| Type-C güç soketi | 5V besleme (VIN üzerinden) |

## Devre Bağlantıları

| ESP8266 Pin | Bağlantı |
|---|---|
| D2 | IR alıcı modül OUT |
| 3.3V | IR alıcı modül VCC |
| GND | IR alıcı modül GND / Transistör emitter |
| VIN (5V) | Transistör collector üzerinden IR LED anot |
| Uygun GPIO | Transistör base (direnç üzerinden) |

> Not: ESP8266 3.3V ile çalışır, ancak IR LED'in daha güçlü sinyal üretebilmesi için VIN pininden (Type-C üzerinden gelen) 5V kullanılmıştır.
<img width="768" height="392" alt="resim" src="https://github.com/user-attachments/assets/d8d150e5-243c-442b-8d61-12b779840154" />
<img width="768" height="426" alt="resim" src="https://github.com/user-attachments/assets/572a5429-4fa8-4a05-9611-7eee1d8341ee" />


## Kurulum

### Gereksinimler

- [PlatformIO](https://platformio.org/) (veya Arduino IDE)
- [IRremote kütüphanesi](https://github.com/Arduino-IRremote/Arduino-IRremote)

### Adımlar

1. Bu depoyu klonlayın:
   ```bash
   git clone https://github.com/<kullanici-adi>/<repo-adi>.git
   ```
2. PlatformIO ile projeyi açın.
3. `PinDefinitionsAndMore.h` dosyasında IR alıcı pini olarak `D2` tanımlıdır, farklı bir pin kullanacaksanız burayı güncelleyin.
4. Kartı ESP8266 olarak seçip kodu yükleyin.

## Kullanım

### 1. Sinyal Okuma

`ReceiveDemo` kodunu yükleyip Seri Port ekranını açın. Kumandanın tuşlarına bastıkça okunan NEC/LG hex kodlarını göreceksiniz. Bu kodları not edin.

### 2. Sinyal Gönderme (Klonlama)

- ESP8266 açıldığında bir WiFi Access Point (AP) oluşturur.
- Telefon veya bilgisayarınızla bu ağa bağlanın; captive portal otomatik açılmazsa tarayıcıdan ESP8266'nın IP adresine gidin (varsayılan: `192.168.4.1`).
- Web arayüzünden, 1. adımda okuduğunuz hex kodları girerek istediğiniz tuşu tetikleyebilirsiniz.

> Not: Kod içindeki `/* power kodun */` gibi alanlar örnektir; kendi kumandanızdan okuduğunuz gerçek kodlarla değiştirmeniz gerekir.

## Bilinen Sınırlamalar

- Bazı modern telefonlar HTTPS tabanlı internet kontrolü yaptığından captive portal otomatik açılmayabilir; bu durumda IP adresine manuel gidin.
- Varsayılan AP şifresi örnek amaçlıdır, kendi şifrenizle değiştirmeniz önerilir.

## Yol Haritası

- [ ] Home Assistant entegrasyonu
- [ ] LoRa üzerinden uzaktan tetikleme
- [ ] Öğrenilen kodların kalıcı (flash/SPIFFS) olarak saklanması

## Kaynak / Blog Yazısı

Projenin detaylı anlatımı için blog yazısına göz atabilirsiniz:
[eon147.com.tr - ESP8266 ile IR Kumanda Klonlama](https://eon147.com.tr/2026/07/08/esp8266-ile-ir-okuma-kopyalama-ve-kizilotesi-led-kullanarak-cogaltma/)

## Lisans

Bu proje [MIT Lisansı](LICENSE) ile lisanslanmıştır.
