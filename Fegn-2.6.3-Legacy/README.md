# Fegn 2.6.3-Legacy

Fegn, Wholf dilinde entegrasyon ve veri yönetimi için kullanılan eski ama güvenilir bir kütüphanedir.

## Özellikler

- Temel API entegrasyonu
- Basit veri yönetimi
- Temel olay yönetimi
- WebSocket desteği
- Cache yönetimi
- Veri doğrulama
- Hata yönetimi

## Kurulum

```wholf
fort import "Fegn-2.6.3-Legacy"
```

## Kullanım Örnekleri

### API Entegrasyonu

```wholf
// API isteği
fegn Api {
    get: ("/users") => {
        Console.log("Kullanıcılar alındı")
    },
    
    post: ("/users", {
        name: "Ahmet",
        email: "ahmet@example.com"
    }) => {
        Console.log("Kullanıcı eklendi")
    }
}
```

### Veri Yönetimi

```wholf
// Veri yönetimi
fegn Data {
    add: ("users", {
        name: "Ahmet",
        email: "ahmet@example.com"
    }) => {
        Console.log("Kullanıcı eklendi")
    },
    
    get: ("users", {
        email: "ahmet@example.com"
    }) => {
        Console.log("Kullanıcı bulundu")
    }
}
```

## Lisans

MIT License
