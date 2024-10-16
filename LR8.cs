using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main()
    {
        // Створюємо об'єкт AES
        Aes aesObject = Aes.Create();
        aesObject.Mode = CipherMode.CFB;  // Використовуємо режим CFB
        aesObject.Key = new byte[32] { 0x9f, 0xbd, 0xe6, 0x4f, 0xad, 0xe1, 0xf3, 0x9d, 0x5e, 0x53, 0x7f, 0xbb, 0x92, 0x96, 0x85, 0x10, 0x9f, 0xbd, 0xe6, 0x4f, 0xad, 0xe1, 0xf3, 0x9d, 0x5e, 0x53, 0x7f, 0xbb, 0x92, 0x96, 0x85, 0x10 };
        aesObject.IV = new byte[] { 0xd7, 0xc9, 0xc5, 0xaf, 0x7f, 0xd1, 0xe8, 0x9e, 0x83, 0xbe, 0x8c, 0xa9, 0xac, 0x7e, 0xd0, 0x00 };

        // Шифрування
        byte[] encryptedData = EncryptData(aesObject, "Hello, this is CFB mode encryption!");
        Console.WriteLine("The encrypted data is:");
        Console.WriteLine(BitConverter.ToString(encryptedData));

        // Розшифрування
        string decryptedData = DecryptData(aesObject, encryptedData);
        Console.WriteLine("\nThe decrypted data is:");
        Console.WriteLine(decryptedData);
    }

    static byte[] EncryptData(Aes aes, string plainText)
    {
        byte[] plainBytes = Encoding.Default.GetBytes(plainText);

        using (MemoryStream ms = new MemoryStream())
        {
            using (CryptoStream cryptoStream = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write))
            {
                cryptoStream.Write(plainBytes, 0, plainBytes.Length);
                cryptoStream.FlushFinalBlock();
            }
            return ms.ToArray();
        }
    }

    static string DecryptData(Aes aes, byte[] encryptedData)
    {
        using (MemoryStream ms = new MemoryStream(encryptedData))
        {
            using (CryptoStream cryptoStream = new CryptoStream(ms, aes.CreateDecryptor(), CryptoStreamMode.Read))
            {
                byte[] decryptedBytes = new byte[encryptedData.Length];
                int bytesRead = cryptoStream.Read(decryptedBytes, 0, decryptedBytes.Length);
                return Encoding.Default.GetString(decryptedBytes, 0, bytesRead);
            }
        }
    }
}
