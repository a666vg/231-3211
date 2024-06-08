#ifndef FUNCTIONS_FOR_SERVER_H
#define FUNCTIONS_FOR_SERVER_H

#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QCryptographicHash>
#include <QPointF>

/**
 * @brief Utility class providing various server-related functions.
 */
class FunctionsForServer
{
public:
    /**
     * @brief Parses the given data.
     * @param data The data to parse.
     * @return Parsed data as QByteArray.
     */
    static QByteArray parse(QString data);

private:
    /**
     * @brief Constants used in SHA-256 algorithm.
     */
    constexpr static const std::array<uint32_t, 64> k = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    /**
     * @brief Initial hash values for SHA-256 algorithm.
     */
    constexpr static const std::array<uint32_t, 8> initial_hash_values = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    /**
     * @brief Authenticates the user.
     * @param log User login.
     * @param pass User password.
     * @return Authentication result as QByteArray.
     */
    static QByteArray auth(QString log, QString pass);

    /**
     * @brief Registers a new user.
     * @param log User login.
     * @param pass User password.
     * @param mail User email.
     * @return Registration result as QByteArray.
     */
    static QByteArray reg(QString log, QString pass, QString mail);

    /**
     * @brief Encrypts the text using Vigenere cipher.
     * @param text The text to encrypt.
     * @param key The encryption key.
     * @return Encrypted text as QByteArray.
     */
    static QByteArray vigenereEncrypt(const QString& text, const QString& key);

    /**
     * @brief Shifts a character by a given number.
     * @param c The character to shift.
     * @param shift The number of positions to shift.
     * @return Shifted character.
     */
    static QChar shiftChar(QChar c, int shift);

    /**
     * @brief Computes the SHA-256 hash of a message.
     * @param message The message to hash.
     * @return SHA-256 hash as QByteArray.
     */
    static QByteArray sha256(const std::string& message);

    // SHA-256 algorithm helper functions
    static uint32_t rotr(uint32_t x, uint32_t n);
    static uint32_t choose(uint32_t e, uint32_t f, uint32_t g);
    static uint32_t majority(uint32_t a, uint32_t b, uint32_t c);
    static uint32_t sig0(uint32_t x);
    static uint32_t sig1(uint32_t x);
    static std::vector<uint8_t> pad_message(const std::string& message);
    static std::array<uint32_t, 8> compute_hash(const std::vector<uint8_t>& padded_message);

    /**
     * @brief Computes spline for the given points.
     * @param pointA First point as QString.
     * @param pointB Second point as QString.
     * @param pointC Third point as QString.
     * @return Computed spline as QByteArray.
     */
    static QByteArray splineMethod(const QString& pointA, const QString& pointB, const QString& pointC);

    /**
     * @brief Converts QString to QPointF.
     * @param point The point as QString.
     * @return Converted point as QPointF.
     */
    static QPointF toPoint(const QString& point);

    /**
     * @brief Computes gradient descent with given parameters.
     * @param learningRate Learning rate as QString.
     * @param maxIterations Maximum iterations as QString.
     * @param precision Precision as QString.
     * @return Result of gradient descent as QByteArray.
     */
    static QByteArray gradientDescent(const QString& learningRate, const QString& maxIterations, const QString& precision);
};

#endif // FUNCTIONS_FOR_SERVER_H
