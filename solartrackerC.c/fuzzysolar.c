#include <stdio.h>
float avgtop, avgdown, avgleft, avgright;
float avgtop_gelap, avgtop_normal, avgtop_terang, avgdown_gelap, avgdown_terang, avgdown_normal;
float out_r1a, out_r1b, out_r2, out_r3, out_r4, out_r5a, out_r5b, out_r6, out_r7, out_r8, out_r9a, out_r9b, out_r10, out_r11, out_r12, out_r13, out_r14, out_r15, out_r16, out_r17, out_r18;
float r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18;
float COAatas, COAbawah;
void ldr_gelap_avgtop()
{
    if (avgtop <= 30)
    {
        avgtop_gelap = 1;
    }
    else if ((avgtop < 40) && (avgtop > 30))
    {
        avgtop_gelap = (40 - avgtop) * 0.1;
    }
    else if (avgtop >= 40)
    {
        avgtop_gelap = 0;
    }
}
// Fuzzification Top
void ldr_normal_avgtop()
{
    if (avgtop <= 30)
    {
        avgtop_normal = 0;
    }
    else if ((avgtop < 50) && (avgtop > 30))
    {
        avgtop_normal = (avgtop - 30) * (0.5);
    }
    else if ((avgtop < 70) && (avgtop >= 50))
    {
        avgtop_normal = (70 - avgtop) * (0.5);
    }
    else if (avgtop >= 70)
    {
        avgtop_normal = 0;
    }
}
void ldr_terang_avgtop()
{
    if (avgtop <= 50)
    {
        avgtop_terang = 0;
    }
    else if ((avgtop < 70) && (avgtop > 50))
    {
        avgtop_terang = (avgtop - 60) * 0.1;
    }

    else if (avgtop >= 70)
    {
        avgtop_terang = 1;
    }
}

// Fuzzification Down
void ldr_gelap_avgdown()
{
    if (avgdown <= 30)
    {
        avgdown_gelap = 1;
    }
    else if ((avgdown < 40) && (avgdown > 30))
    {
        avgdown_gelap = (40 - avgdown) * 0.1;
    }
    else if (avgdown >= 40)
    {
        avgdown_gelap = 0;
    }
}

void ldr_normal_avgdown()
{
    if (avgdown <= 30)
    {
        avgdown_normal = 0;
    }
    else if ((avgdown < 50) && (avgdown > 30))
    {
        avgdown_normal = (avgdown - 30) * (0.5);
    }
    else if ((avgdown < 70) && (avgdown >= 50))
    {
        avgdown_normal = (70 - avgdown) * (0.5);
    }
    else if (avgtop >= 70)
    {
        avgdown_normal = 0;
    }
}
void ldr_terang_avgdown()
{
    if (avgdown <= 50)
    {
        avgdown_terang = 0;
    }
    else if ((avgdown < 70) && (avgdown > 50))
    {
        avgdown_terang = (avgdown - 60) * 0.1;
    }

    else if (avgdown >= 70)
    {
        avgdown_terang = 1;
    }
}
void fuzzification()
{
    ldr_gelap_avgdown();
    ldr_gelap_avgtop();
    ldr_normal_avgdown();
    ldr_normal_avgtop();
    ldr_terang_avgdown();
    ldr_terang_avgtop();
}

float min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else if (b > a)
    {
        return b;
    }
    else
    {
        return a;
    }
}
void rule()
{
    fuzzification();
    // if atas gelap bawah gelap motor off
    r1 = min(avgtop_gelap, avgdown_gelap);
    out_r1a = (5 * r1) - 5;
    out_r1b = 5 - (5 * r1);
    // if atas gelap bawah normal motor ccw
    r2 = min(avgtop_gelap, avgdown_normal);
    out_r2 = (-5) * (r2 + 1);
    // if atas gelap bawah terang motor ccw
    r3 = min(avgtop_gelap, avgdown_terang);
    out_r3 = (-5) * (r3 + 1);
    // if atas normal bawah gelap motor cw
    r4 = min(avgtop_normal, avgdown_gelap);
    out_r4 = (5 * r4) + 5;
    // if atas normal bawah normal motor off
    r5 = min(avgtop_normal, avgdown_normal);
    out_r5a = (5 * r5) - 5;
    out_r5b = 5 - (5 * r5);
    // if atas normal bawah terang motor ccw
    r6 = min(avgtop_normal, avgdown_terang);
    out_r6 = (-5) * (r6 + 1);
    // if atas terang bawah gelap motor cw
    r7 = min(avgtop_terang, avgdown_gelap);
    out_r7 = (5 * r7) + 5;
    // if atas terang bawah normal motor cw
    r8 = min(avgtop_terang, avgdown_normal);
    out_r8 = (5 * r8) + 5;
    // if atas terang bawah terang motor off
    r9 = min(avgtop_terang, avgdown_terang);
    out_r9a = (5 * r9) - 5;
    out_r9b = 5 - (5 * r9);
}

float deffuzyfication()
{
    rule();
    COAatas = (r1 * (out_r1a + out_r1b) + r2 * (out_r2) + r3 * (out_r3) + r4 * (out_r4) + r5 * (out_r5a + out_r5b) + r6 * (out_r6) + r7 * (out_r7) + r8 * (out_r8) + r9 * (out_r9a + out_r9b));
    COAbawah = (r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9);
    return COAatas / COAbawah;
}

void setup()
{
    avgtop = 20;
    avgdown = 80;
    rule();
    int a = deffuzyfication();

    printf("Deffuzification : %f", a);
}
