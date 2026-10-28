# Псевдокод — Сэдэв №4: Цахилгааны төлбөр

Блок схем (`quest.fprg`)-ийн блок бүртэй дарааллаараа тохирно.

## Main

```
ЭХЛЭХ Main
    totalKwh ← 0, totalBill ← 0
    maxKwh ← -1, maxBill ← 0, maxMonth ← 0
    ХЭВЛЭХ "=== TSAHILGAANY TULBUR TOOTSOOLUUR ==="

    // 1. Оролт ба шалгалт (do-while)
    ДАВТАХ
        ХЭВЛЭХ "Ger buliin gishuudiin too (1-20): "
        УНШИХ residents
        ХЭРЭВ residents < 1 ЭСВЭЛ residents > 20 БОЛ ХЭВЛЭХ "Aldaa!..."
    ХҮРТЭЛ НЬ БИШ (residents < 1 ЭСВЭЛ residents > 20)

    ДАВТАХ
        ХЭВЛЭХ "Neg hunii sariin dundaj hereglee, kVt.ts (0-500): "
        УНШИХ perPerson
        ХЭРЭВ perPerson <= 0 ЭСВЭЛ perPerson > 500 БОЛ ХЭВЛЭХ "Aldaa!..."
    ХҮРТЭЛ НЬ БИШ (perPerson <= 0 ЭСВЭЛ perPerson > 500)

    ДАВТАХ
        ХЭВЛЭХ "Ahmad nastan baigaa yu? (1 - tiim, 0 - ugui): "
        УНШИХ elder
        ХЭРЭВ elder ≠ 0 БА elder ≠ 1 БОЛ ХЭВЛЭХ "Aldaa!..."
    ХҮРТЭЛ НЬ БИШ (elder ≠ 0 БА elder ≠ 1)

    // 2. 12 сарын хүснэгт
    ХЭВЛЭХ хүснэгтийн толгой
    month = 1-ээс 12 хүртэл ДАВТАХ
        // Улирлын коэффициент (else-if шат)
        ХЭРЭВ month = 12 ЭСВЭЛ month = 1 БОЛ coef ← 1.5
        ҮГҮЙ БӨГӨӨД month = 2            БОЛ coef ← 1.4
        ҮГҮЙ БӨГӨӨД month = 11           БОЛ coef ← 1.3
        ҮГҮЙ БӨГӨӨД month = 3 ЭСВЭЛ 10   БОЛ coef ← 1.2
        ҮГҮЙ БӨГӨӨД month = 4 ЭСВЭЛ 9    БОЛ coef ← 1.0
        ҮГҮЙ БӨГӨӨД month = 5 ЭСВЭЛ 8    БОЛ coef ← 0.8
        ҮГҮЙ БОЛ                             coef ← 0.7

        kwh  ← residents × perPerson × coef
        bill ← CalcBill(kwh, elder)            // дэд алгоритм

        ХЭРЭВ kwh <= 150      БОЛ tier ← "1-Hemnelt"
        ҮГҮЙ БӨГӨӨД kwh <= 300 БОЛ tier ← "2-Dundaj"
        ҮГҮЙ БОЛ                  tier ← "3-Undur"

        ХЭВЛЭХ month | kwh | tier | bill
        totalKwh  ← totalKwh + kwh
        totalBill ← totalBill + bill

        // 3. Хайлт: хамгийн их зарцуулсан сар
        ХЭРЭВ kwh > maxKwh БОЛ
            maxKwh ← kwh, maxBill ← bill, maxMonth ← month
    ДАВТАЛТ ДУУСАХ

    ХЭВЛЭХ нийт kwh, нийт төлбөр
    ХЭВЛЭХ сарын дундаж төлбөр = totalBill / 12
    ХЭВЛЭХ maxMonth, maxKwh, maxBill
    ДУУДАХ PrintAdvice(maxKwh)                 // Call блок
ДУУСАХ
```

## Function CalcBill(kwh, elder) → bill

```
    ХЭРЭВ kwh <= 150 БОЛ
        bill ← kwh × 150
    ҮГҮЙ БӨГӨӨД kwh <= 300 БОЛ
        bill ← 150×150 + (kwh − 150) × 200
    ҮГҮЙ БОЛ
        bill ← 150×150 + 150×200 + (kwh − 300) × 280
    bill ← bill + 2000                         // суурь хураамж
    ХЭРЭВ elder = 1 БА kwh <= 200 БОЛ
        bill ← bill × 0.9                      // 10% хөнгөлөлт
    БУЦААХ bill
```

## Function PrintAdvice(maxKwh)

```
    ХЭРЭВ maxKwh > 300      БОЛ ХЭВЛЭХ "3-r shatlald orson baina! ..."
    ҮГҮЙ БӨГӨӨД maxKwh > 150 БОЛ ХЭВЛЭХ "2-r shatlald orson baina. ..."
    ҮГҮЙ БОЛ                    ХЭВЛЭХ "Mash hemnelttei! ..."
```
