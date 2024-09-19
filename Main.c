#include "STD_TYPES.h"
#include "MDIO/MDIO_Interface.h"
#include "MDIO/MDIO_Private.h"
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"
#include <util/delay.h>

#define C_CPU 8000000UL // Define CPU frequency for accurate delay calculations
void flash_leds();
void shift_left();
void shift_right();
void converge_leds();
void diverge_leds();
void ping_pong();
void snake_effect();
void converge_diverge_leds();

u8 pressedKey;

int main(void)
{
    // Initialize the MDIO and LCD
    MDIO_IntialPins();  // Initialize all necessary pins (assuming this function sets up ports and pins)
    HLCD_VoidLcdIint(); // Initialize the LCD

    while (1)
    {
        HKPD_u8GetPressedKey(&pressedKey); // Get the pressed key from the keypad

        switch (pressedKey)
        {
        case '1':
            flash_leds(); // Call flash_leds when '1' is pressed
            break;
        case '2':
            shift_left(); // Placeholder for the shift_left function
            break;
        case '3':
            shift_right(); // Placeholder for the shift_right function
            break;
        case '4':
            converge_leds(); // Placeholder for the converge_leds function
            break;
        case '5':
            diverge_leds(); // Placeholder for the diverge_leds function
            break;
        case '6':
            ping_pong(); // Placeholder for the ping_pong function
            break;
        case '7':
            snake_effect(); // Placeholder for the snake_effect function
            break;
        case '8':
            converge_diverge_leds(); // Placeholder for the converge_diverge_leds function
            break;
        default:
            MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs if no valid key is pressed
            break;
        }
    }

}

void flash_leds()
{
	HLCD_VoidLcdClear();

HLCD_u8WriteStr("Flash Mode");
    while (1)
    {
        MDIO_u8SetPortValue(MDIO_PORTB, 0xFF); // Turn on all LEDs
        _delay_ms(500);
        MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
        _delay_ms(500);

        HKPD_u8GetPressedKey(&pressedKey); // Continuously check for a key press
        if (pressedKey != '1')
        {
            break; // Exit the loop if any key other than '1' is pressed
        }
    }

    // After the loop exits, turn off all LEDs
    MDIO_u8SetPortValue(MDIO_PORTB, 0x00);
}


void shift_left()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Shift Left Mode");
    while (1)
    {
        // Iterate from bit 0 to bit 7
        for (u8 i = 0; i < 8; i++)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // Shift the LED to the left
            _delay_ms(250); // Delay between each shift

            HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
            if (pressedKey != '2') // If any key other than '2' is pressed
            {
                // Exit the loop
                MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
                return; // Exit the function
            }
        }
    }
}

void shift_right()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Shift Right Mode");
    while (1)
    {
        // Iterate from bit 7 to bit 0
        for (int8_t i = 7; i >= 0; i--)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // Shift the LED to the right
            _delay_ms(250); // Delay between each shift

            HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
            if (pressedKey != '3') // If any key other than '3' is pressed
            {
                // Exit the loop
                MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
                return; // Exit the function
            }
        }
    }
}
void converge_leds()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Coverge Mode");
    while (1)
    {
        for (u8 i = 0; i < 4; i++)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i) | (1 << (7 - i))); // Converging LEDs
            _delay_ms(300);

            HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
            if (pressedKey != '4') // Exit if key is no longer '4'
            {
                MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
                return; // Exit the function
            }
        }
    }
}

void diverge_leds()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Diverge Mode");
    while (1)
    {
        for (int8_t i = 3; i >= 0; i--)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i) | (1 << (7 - i))); // Diverging LEDs
            _delay_ms(300);

            HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
            if (pressedKey != '5') // Exit if key is no longer '5'
            {
                MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
                return; // Exit the function
            }
        }
    }
}

void ping_pong()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Ping Pong Mode");
    while (1)
    {
        // Moving right
        for (u8 i = 0; i < 8; i++)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // LED shifts right
            _delay_ms(150);
        }
        // Moving left
        for (int8_t i = 6; i >= 0; i--)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // LED shifts left
            _delay_ms(150);
        }

        HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
        if (pressedKey != '6') // Exit if key is no longer '6'
        {
            MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
            return; // Exit the function
        }
    }
}

void snake_effect()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Snake Effect Mode");
    while (1)
    {
        // Snake moving right
        for (u8 i = 0; i < 8; i++)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // LED shifts right
            _delay_ms(200);
        }
        // Snake moving left
        for (int8_t i = 6; i >= 0; i--)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i)); // LED shifts left
            _delay_ms(200);
        }

        HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
        if (pressedKey != '7') // Exit if key is no longer '7'
        {
            MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
            return; // Exit the function
        }
    }
}

void converge_diverge_leds()
{
	HLCD_VoidLcdClear();
	HLCD_u8WriteStr("Converge Diverge Mode");
    while (1)
    {
        // Converging LEDs
        for (u8 i = 0; i < 4; i++)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i) | (1 << (7 - i))); // LEDs move towards center
            _delay_ms(300);
        }
        // Diverging LEDs
        for (int8_t i = 3; i >= 0; i--)
        {
            MDIO_u8SetPortValue(MDIO_PORTB, (1 << i) | (1 << (7 - i))); // LEDs move away from center
            _delay_ms(300);
        }

        HKPD_u8GetPressedKey(&pressedKey); // Continuously check for key press
        if (pressedKey != '8') // Exit if key is no longer '8'
        {
            MDIO_u8SetPortValue(MDIO_PORTB, 0x00); // Turn off all LEDs
            return; // Exit the function
        }
    }
}
