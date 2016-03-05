package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

/**
 * Created by rice on 1/10/16.
 */
public class MainMemoryTest {
  @Test
  public void TestIsAligned() {
    MainMemory m = new MainMemory(0);
    assertEquals(true, m.isAccessAligned(0, 4));
    assertEquals(false, m.isAccessAligned(1, 4));
    assertEquals(true, m.isAccessAligned(4, 4));
    assertEquals(true, m.isAccessAligned(8, 4));
    assertEquals(true, m.isAccessAligned(2, 2));
    assertEquals(false, m.isAccessAligned(1, 2));
  }

  @Test
  public void TestBytesToInteger() {
    MainMemory m = new MainMemory(0);
    assertEquals(0, intsToInteger(m,0,0,0,0));
    assertEquals(1, intsToInteger(m,0,0,0,1));
    assertEquals(128, intsToInteger(m,0,0,0,0x80));
    assertEquals(255, intsToInteger(m,0,0,0,0xff));
    assertEquals(-1, intsToInteger(m,0xff,0xff,0xff,0xff));
    assertEquals(Integer.MAX_VALUE, intsToInteger(m,0x7f,0xff,0xff,0xff));
    assertEquals(Integer.MIN_VALUE, intsToInteger(m,0x80,0,0,0));
  }

  @Test
  public void TestIntegerToBytes() {
    MainMemory m = new MainMemory(0);
    bytesEqual(0, 0, 0, 0, m.integerToBytes(0));
    bytesEqual(0, 0, 0, 1, m.integerToBytes(1));
    bytesEqual(0, 0, 0, 0x80, m.integerToBytes(128));
    bytesEqual(0, 0, 0, 0xff, m.integerToBytes(255));
    bytesEqual(0xff, 0xff, 0xff, 0xff, m.integerToBytes(-1));
    bytesEqual(0x7f, 0xff, 0xff, 0xff, m.integerToBytes(Integer.MAX_VALUE));
    bytesEqual(0x80, 0, 0, 0, m.integerToBytes(Integer.MIN_VALUE));
  }


  @Test
  public void TestSetGet() throws AbstractMainMemory.InvalidAddressException {
    byte[] intCase = {1,2,3,4};
    byte[] longCase = {1,2,3,4,5,6,7,8};
    byte[] shortCase = {9};

    MainMemory m = new MainMemory(128);
    m.set(8, intCase);
    bytesEqual2(intCase, m.get(8, 4));

    m.set(4, longCase);
    bytesEqual2(longCase, m.get(4, 8));

    m.set(0, shortCase);
    bytesEqual2(shortCase, m.get(0, 1));

    m.set(127, shortCase);
    bytesEqual2(shortCase, m.get(127, 1));

    try {
      m.set(-1, longCase);
      fail();
    } catch (Exception e) {}
    try {
      m.get(-1, 1);
      fail();
    } catch (Exception e) {}
    try {
      m.set(121, longCase);
      fail();
    } catch (Exception e) {}
    try {
      m.get(121, 8);
      fail();
    } catch (Exception e) {}
  }

  private int intsToInteger(MainMemory m, int a, int b, int c, int d) {
    return m.bytesToInteger((byte)a,(byte)b,(byte)c,(byte)d);
  }

  private void bytesEqual(int a, int b, int c, int d, byte[] bytes) {
    assertEquals((byte)a,bytes[0]);
    assertEquals((byte)b,bytes[1]);
    assertEquals((byte)c,bytes[2]);
    assertEquals((byte)d,bytes[3]);
  }

  private void bytesEqual2(byte[] a, byte[] b) {
    assertEquals(a.length, b.length);
    for(int i=0; i < a.length; i++) {
      assertEquals(a[i],b[i]);
    }
  }
}
