#include <BLEDevice.h>

BLEService *pService = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
BLEServer* pServer;


class MyCallbacks: public BLECharacteristicCallbacks {
   //Serial.println("1");
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue(); 
        pCharacteristic->setValue("12");
        if (value.length() > 0) {
        Serial.print("Received value: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.print(value[i]);
        }
        Serial.println();
    }
    }
        
        // Действия по обработке записанных данных
    
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("Hello new user!");
    }
    void onDisconnect(BLEServer* pServer) {
        // Получаем MAC-адрес отключившегося устройства
       
        Serial.print("Disconnected device");
       
        
        // Перезапуск рекламы для оставания доступным для обнаружения
        pServer->startAdvertising();
    }
};

void setup() {
  
    Serial.begin(115200);
    BLEDevice::init("ESP32");
   
    // Создание сервиса с определенным UUID
    //pService = BLEDevice::createService("UUID");
    
    pServer = BLEDevice::createServer();
    
    BLEService *pService = pServer->createService("180D");
    
    
    // Создание характеристики с определенным UUID и свойствами (например, чтение и запись)
    pCharacteristic = pService->createCharacteristic(
        "180D", 
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE 
    );
    
    
    pCharacteristic->setCallbacks(new MyCallbacks());
    pServer->setCallbacks(new MyServerCallbacks());
    // Запуск сервиса
    
    pService->start();
    
    // Настройка рекламы, чтобы другие устройства могли видеть ваше устройство
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    
    pAdvertising->addServiceUUID(pService->getUUID());
    pAdvertising->start();
    
}

void loop() {
    // Основной код программы
    //Serial.println("2");
}
