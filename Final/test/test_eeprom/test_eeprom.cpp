/**
 * On-device unit tests for the register-level EEPROM library.
 *
 * These run ON the Uno: `pio test -e uno` builds this file, flashes it,
 * then reads Unity's report back over the serial port.
 *
 * Everything written here lives in a reserved scratch window near the top
 * of the 1024-byte EEPROM so the Contact/Message schema is never touched.
 * (test_boundary_addresses is the one exception: it pokes address 0x0000.)
 */

#include <Arduino.h>
#include <unity.h>
#include <EEPROM.h>

// Flip to 1 once EEPROM::read/write are widened to uint16_t (see notes).
// The 16-bit tests below are skipped until then.
#define EEPROM_HAS_16BIT_API 0

// Uno ATmega328P has 1 KiB of EEPROM: 0x000 - 0x3FF (see E2END).
static const uint16_t EEPROM_LAST_ADDR = 0x3FF;

// Reserved scratch window, 0x300 - 0x3F0. Each library call touches addr and
// addr + 1, so the window stops short of the end of the address space and
// every test offset below stays inside it.
static const uint16_t SCRATCH_START = 0x300;
static const uint16_t SCRATCH_END   = 0x3F0;

// Offsets into the scratch window, one block per test so nothing overlaps.
static const uint16_t OFF_PATTERN    = 0x00;  // 32 bytes
static const uint16_t OFF_SPILL      = 0x30;
static const uint16_t OFF_IDEMPOTENT = 0x40;
static const uint16_t OFF_SEQUENCE   = 0x50;  // 8 bytes
static const uint16_t OFF_SURVIVES   = 0x60;
static const uint16_t OFF_TRAFFIC    = 0x70;  // 16 bytes
static const uint16_t OFF_WALKING    = 0x80;  // 16 bytes
static const uint16_t OFF_WORD       = 0xA0;  // 6 x 16-bit samples
static const uint16_t OFF_WORD_SPILL = 0xC0;

void setUp(void) {
  // Runs before every test. Nothing to reset: the scratch window is primed
  // once in main() and each test owns a separate block of it.
}

void tearDown(void) {
  // Runs after every test, pass or fail.
}

// ---------------------------------------------------------------- helpers --

// The library writes to addr and addr + 1 on every call, so a byte array
// cannot be primed with one pass of unconditional writes. Read first and
// skip cells that already hold the wanted value: reads are free, and EEPROM
// cells are rated for only ~100k write cycles.
static void primeScratch(uint8_t pattern) {
  for (uint16_t addr = SCRATCH_START; addr <= SCRATCH_END; addr++) {
    if (EEPROM::read(addr) != pattern) {
      EEPROM::write(addr, pattern);
    }
  }
}

static void assertRangeEquals(uint16_t from, uint16_t to, uint8_t expected,
                              const char* message) {
  for (uint16_t addr = from; addr <= to; addr++) {
    TEST_ASSERT_EQUAL_MESSAGE(expected, EEPROM::read(addr), message);
  }
}

static void assertRangeUnchanged(uint16_t from, uint16_t to, uint8_t expected) {
  assertRangeEquals(from, to, expected, "neighbour cell was clobbered");
}

// ------------------------------------------------------------------ tests --

// Write a recognizable pattern, then read every cell back.
void test_write_then_read(void) {
  primeScratch(0x00);

  const uint16_t base = SCRATCH_START + OFF_PATTERN;
  for (uint8_t i = 0; i < 32; i++) {
    EEPROM::write(base + i, static_cast<uint8_t>(0xA0 + i));
  }

  for (uint8_t i = 0; i < 32; i++) {
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(static_cast<uint8_t>(0xA0 + i),
                                   EEPROM::read(base + i), "readback mismatch");
  }
}

// Walking ones catches stuck bits and shorted data lines.
void test_walking_ones(void) {
  const uint16_t base = SCRATCH_START + OFF_WALKING;

  for (uint8_t bit = 0; bit < 8; bit++) {
    const uint8_t pattern = static_cast<uint8_t>(1u << bit);
    for (uint16_t addr = base; addr < base + 16; addr++) {
      EEPROM::write(addr, pattern);
      TEST_ASSERT_EQUAL_HEX8_MESSAGE(pattern, EEPROM::read(addr),
                                     "walking-ones failure");
    }
  }
}

// Writing one address must not disturb its neighbours.
void test_writes_do_not_spill(void) {
  primeScratch(0xA5);

  const uint16_t target = SCRATCH_START + OFF_SPILL;
  EEPROM::write(target, 0x5A);

  TEST_ASSERT_EQUAL_HEX8(0x5A, EEPROM::read(target));

  // The library's second byte write lands on target + 1, so that cell is the
  // library's own storage. Only assert on the cells outside of it.
  assertRangeUnchanged(target - 2, target - 1, 0xA5);
  assertRangeUnchanged(target + 2, target + 4, 0xA5);
}

// Reading is non-destructive and repeatable.
void test_reads_are_idempotent(void) {
  primeScratch(0x00);

  const uint16_t addr = SCRATCH_START + OFF_IDEMPOTENT;
  EEPROM::write(addr, 0xC3);

  for (uint8_t i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL_HEX8(0xC3, EEPROM::read(addr));
  }
}

// The busy-wait on EEPE must actually finish each write. Two back-to-back
// calls would otherwise drop the second one.
void test_consecutive_writes(void) {
  primeScratch(0x00);

  const uint16_t base = SCRATCH_START + OFF_SEQUENCE;
  const uint8_t data[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

  for (uint8_t i = 0; i < sizeof(data); i++) {
    EEPROM::write(base + i, data[i]);
  }

  for (uint8_t i = 0; i < sizeof(data); i++) {
    TEST_ASSERT_EQUAL_HEX_MESSAGE(data[i], EEPROM::read(base + i),
                                  "dropped a byte");
  }
}

// First and last usable addresses.
void test_boundary_addresses(void) {
  const uint8_t lowValue  = 0x17;
  const uint8_t highValue = 0xE9;

  // Pokes address 0, which is where the schema will eventually start.
  EEPROM::write(0x0000, lowValue);
  EEPROM::write(SCRATCH_END, highValue);

  TEST_ASSERT_EQUAL_HEX8(lowValue, EEPROM::read(0x0000));
  TEST_ASSERT_EQUAL_HEX8(highValue, EEPROM::read(SCRATCH_END));

  // Documents the assumption the library makes about the chip size.
  TEST_ASSERT_EQUAL_UINT16(0x3FF, EEPROM_LAST_ADDR);
}

// A value must survive unrelated writes elsewhere, i.e. it really is in a
// non-volatile cell and not in a register that later traffic overwrites.
void test_data_survives_other_traffic(void) {
  primeScratch(0x00);

  const uint16_t keepAddr = SCRATCH_START + OFF_SURVIVES;
  EEPROM::write(keepAddr, 0x7E);

  const uint16_t traffic = SCRATCH_START + OFF_TRAFFIC;
  for (uint16_t addr = traffic; addr < traffic + 16; addr++) {
    EEPROM::write(addr, 0x11);
  }

  TEST_ASSERT_EQUAL_HEX8(0x7E, EEPROM::read(keepAddr));
}

#if EEPROM_HAS_16BIT_API
// Payloads in Message.h are uint16_t, so this is the path Memory.cpp will
// need. Only compiles once EEPROM::read/write are widened to uint16_t.
void test_sixteen_bit_round_trip(void) {
  primeScratch(0x00);

  const uint16_t base = SCRATCH_START + OFF_WORD;
  const uint16_t samples[] = { 0x0000, 0x00FF, 0x0100, 0x1234, 0x8000, 0xFFFF };
  const uint8_t count = sizeof(samples) / sizeof(samples[0]);

  for (uint8_t i = 0; i < count; i++) {
    EEPROM::write(base + (4u * i), samples[i]);
  }

  for (uint8_t i = 0; i < count; i++) {
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(samples[i], EEPROM::read(base + (4u * i)),
                                    "16-bit round trip failed");
  }
}

void test_sixteen_bit_no_spill(void) {
  primeScratch(0x3C);

  const uint16_t target = SCRATCH_START + OFF_WORD_SPILL;
  EEPROM::write(target, 0xBEEF);

  TEST_ASSERT_EQUAL_HEX16(0xBEEF, EEPROM::read(target));

  assertRangeUnchanged(target - 2, target - 1, 0x3C);
  assertRangeUnchanged(target + 2, target + 4, 0x3C);
}
#endif

// -------------------------------------------------------------------- main --

int main() {
  // Because this file supplies its own main(), the Arduino core's main() is
  // never linked, so init() has to be called by hand. init() configures the
  // clock prescaler, starts Timer0 and enables global interrupts; without it
  // millis()/micros()/delay() deadlock and nothing is ever printed.
  init();

  // Must match test_speed in platformio.ini.
  Serial.begin(115200);

  // Uploading resets the board; give the test runner time to grab the port
  // before Unity starts printing.
  delay(1000);

  UNITY_BEGIN();

  RUN_TEST(test_write_then_read);
  RUN_TEST(test_walking_ones);
  RUN_TEST(test_writes_do_not_spill);
  RUN_TEST(test_reads_are_idempotent);
  RUN_TEST(test_consecutive_writes);
  RUN_TEST(test_boundary_addresses);
  RUN_TEST(test_data_survives_other_traffic);

#if EEPROM_HAS_16BIT_API
  RUN_TEST(test_sixteen_bit_round_trip);
  RUN_TEST(test_sixteen_bit_no_spill);
#endif

  return UNITY_END();
}
