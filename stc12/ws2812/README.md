# ws2812 driver
# main function
* support show single char(lcd1602 encoding)
* support scroll message(lcd1602 encoding)

# hardware config
* 32M crystal oscillator(may be reduced to 16M, but code need to be modified for the macro WRITE0&WRITE1)
* make sure the power supply is enough, or the mcu will restart abnormally.
* 8x8 ws2812 zig-zag cascading
```mermaid
graph TB
    row0 --> row1
    row1 --> row2
    row2 --> row3
    row3 --> row4
    row4 --> row5
    row5 --> row6
    row6 --> row7
    subgraph row0
        direction LR
        0 --> 1
        1 --> 2
        2 --> 3
        3 --> 4
        4 --> 5
        5 --> 6
        6 --> 7
    end
    subgraph row1
        direction RL
        15 --> 14
        14 --> 13
        13 --> 12
        12 --> 11
        11 --> 10
        10 --> 9
        9 --> 8
    end
    subgraph row2
        direction LR
        16 --> 17
        17 --> 18
        18 --> 19
        19 --> 20
        20 --> 21
        21 --> 22
        22 --> 23
    end
    subgraph row3
    end
    subgraph row4
    end
    subgraph row5
    end
    subgraph row6
    end
    subgraph row7
        direction RL
        63 --> 62
        62 --> 61
        61 --> 60
        60 --> 59
        59 --> 58
        58 --> 57
        57 --> 56
    end
```

