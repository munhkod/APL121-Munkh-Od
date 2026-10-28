/*
 * APL121 - Бие даалт №1 (Code Quest)
 * Сэдэв №4: Цахилгааны төлбөр
 *
 * Гэр бүлийн гишүүдийн тоо, нэг хүний сарын дундаж хэрэглээ,
 * ахмад настны хөнгөлөлтийг оруулаад 12 сарын цахилгааны төлбөрийг
 * шатлалтай тарифаар тооцоолж, хамгийн их зарцуулсан сарыг олно.
 *
 * Компайл:  gcc main.c -o main
 * Ажиллуулах: ./main   (Windows: main.exe)
 */
#include <stdio.h>

/* ---- Өөрийн тогтоосон дүрмүүд (README-д тайлбарласан) ---- */
#define TIER1_LIMIT   150.0   /* 1-р шатлалын дээд хязгаар, кВт.ц   */
#define TIER2_LIMIT   300.0   /* 2-р шатлалын дээд хязгаар, кВт.ц   */
#define TIER1_PRICE   150.0   /* 0-150 кВт.ц:   1 кВт.ц = 150 төг   */
#define TIER2_PRICE   200.0   /* 151-300 кВт.ц: 1 кВт.ц = 200 төг   */
#define TIER3_PRICE   280.0   /* 300-аас дээш:  1 кВт.ц = 280 төг   */
#define SERVICE_FEE   2000.0  /* Сар бүрийн суурь хураамж, төг      */
#define ELDER_LIMIT   200.0   /* Хөнгөлөлт эдлэх хэрэглээний хязгаар */
#define ELDER_RATE    0.90    /* Ахмад настны 10% хөнгөлөлт          */

/* Дэд алгоритм 1 (Flowgorithm: CalcBill функц)
 * Нэг сарын хэрэглээ (кВт.ц) -> төлөх дүн (төг) */
double calcBill(double kwh, int elder)
{
    double bill;

    /* Шатлалтай тариф: шатлал бүрийн хэсгийг өөрийн үнээр тооцно */
    if (kwh <= TIER1_LIMIT) {
        bill = kwh * TIER1_PRICE;
    } else if (kwh <= TIER2_LIMIT) {
        bill = TIER1_LIMIT * TIER1_PRICE
             + (kwh - TIER1_LIMIT) * TIER2_PRICE;
    } else {
        bill = TIER1_LIMIT * TIER1_PRICE
             + (TIER2_LIMIT - TIER1_LIMIT) * TIER2_PRICE
             + (kwh - TIER2_LIMIT) * TIER3_PRICE;
    }
    bill = bill + SERVICE_FEE;

    /* Ахмад настантай БӨГӨӨД хэмнэлттэй хэрэглэсэн бол 10% хөнгөлнө */
    if (elder == 1 && kwh <= ELDER_LIMIT) {
        bill = bill * ELDER_RATE;
    }
    return bill;
}

/* Дэд алгоритм 2 (Flowgorithm: PrintAdvice процедур, Call блок)
 * Хамгийн их хэрэглээнээс хамаарч хэмнэлтийн зөвлөмж хэвлэнэ */
void printAdvice(double maxKwh)
{
    printf("Zovlomj: ");
    if (maxKwh > TIER2_LIMIT) {
        printf("3-r shatlald orson baina! Tsahilgaan khalaagchaa tsagaar untraaj, LED gerel ashiglaarai.\n");
    } else if (maxKwh > TIER1_LIMIT) {
        printf("2-r shatlald orson baina. Hereggui ued tonogloloo zalguuraas salgaarai.\n");
    } else {
        printf("Mash hemnelttei! Ene dadlaa hadgalaarai.\n");
    }
}

int main(void)
{
    int residents;      /* Гэр бүлийн гишүүдийн тоо (1-20)        */
    double perPerson;   /* Нэг хүний сарын дундаж хэрэглээ, кВт.ц */
    int elder;          /* Ахмад настан байгаа эсэх (1/0)         */

    int month;
    double coef, kwh, bill;
    double totalKwh = 0, totalBill = 0;
    double maxKwh = -1, maxBill = 0;
    int maxMonth = 0;

    printf("=== TSAHILGAANY TULBUR TOOTSOOLUUR ===\n");

    /* ---- Оролт ба шалгалт (do-while) ---- */
    do {
        printf("Ger buliin gishuudiin too (1-20): ");
        if (scanf("%d", &residents) != 1) {      /* тоо биш зүйл бичвэл */
            residents = -1;
            while (getchar() != '\n');
        }
        if (residents < 1 || residents > 20) {
            printf("Aldaa! 1-20 hoorond too oruulna uu.\n");
        }
    } while (residents < 1 || residents > 20);

    do {
        printf("Neg hunii sariin dundaj hereglee, kVt.ts (0-500): ");
        if (scanf("%lf", &perPerson) != 1) {
            perPerson = -1;
            while (getchar() != '\n');
        }
        if (perPerson <= 0 || perPerson > 500) {
            printf("Aldaa! 0-ees ih, 500-aas baga too oruulna uu.\n");
        }
    } while (perPerson <= 0 || perPerson > 500);

    do {
        printf("Ahmad nastan baigaa yu? (1 - tiim, 0 - ugui): ");
        if (scanf("%d", &elder) != 1) {
            elder = -1;
            while (getchar() != '\n');
        }
        if (elder != 0 && elder != 1) {
            printf("Aldaa! Zuvhun 0 esvel 1 oruulna uu.\n");
        }
    } while (elder != 0 && elder != 1);

    /* ---- 12 сарын хүснэгт ---- */
    printf("\n%-5s %10s %-12s %12s\n", "Sar", "kVt.ts", " Shatlal", "Tulbur(tug)");
    printf("-------------------------------------------\n");

    for (month = 1; month <= 12; month++) {
        /* Улирлын коэффициент: өвөл их, зун бага хэрэглэнэ */
        if (month == 12 || month == 1) {
            coef = 1.5;
        } else if (month == 2) {
            coef = 1.4;
        } else if (month == 11) {
            coef = 1.3;
        } else if (month == 3 || month == 10) {
            coef = 1.2;
        } else if (month == 4 || month == 9) {
            coef = 1.0;
        } else if (month == 5 || month == 8) {
            coef = 0.8;
        } else {                       /* 6, 7-р сар */
            coef = 0.7;
        }

        kwh = residents * perPerson * coef;
        bill = calcBill(kwh, elder);

        /* Шатлалын нэр (else-if шат) */
        printf("%-5d %10.2f ", month, kwh);
        if (kwh <= TIER1_LIMIT) {
            printf("%-12s", " 1-Hemnelt");
        } else if (kwh <= TIER2_LIMIT) {
            printf("%-12s", " 2-Dundaj");
        } else {
            printf("%-12s", " 3-Undur");
        }
        printf(" %12.2f\n", bill);

        totalKwh = totalKwh + kwh;
        totalBill = totalBill + bill;

        /* Хайлт: хамгийн их зарцуулсан сар (анхных нь үлдэнэ) */
        if (kwh > maxKwh) {
            maxKwh = kwh;
            maxBill = bill;
            maxMonth = month;
        }
    }

    printf("-------------------------------------------\n");
    printf("%-5s %10.2f %-12s %12.2f\n", "Niit", totalKwh, "", totalBill);
    printf("Sariin dundaj tulbur: %.2f tug\n", totalBill / 12);
    printf("Hamgiin ih zartsuulsan sar: %d-r sar (%.2f kVt.ts, %.2f tug)\n",
           maxMonth, maxKwh, maxBill);

    printAdvice(maxKwh);

    return 0;
}
