-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

-- Retrieve the crime scene report on July 28, 2021 for Humphrey Street.
SELECT description FROM crime_scene_reports
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = "Humphrey Street";
-- Result: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- – each of their interview transcripts mentions the bakery.

SELECT transcript FROM interviews
    WHERE
    (
        year = 2021
        AND month = 7
        AND day = 28
    )
    AND
        LOWER(transcript) LIKE "%bakery%";
-- 1. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--    If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- 2. I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking
--    by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- 3. As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that
--    they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to
--    purchase the flight ticket. |
-- 4. I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

-- Check ATM Transactions on Leggett Street
SELECT name,phone_number,passport_number,license_plate FROM people
WHERE license_plate IN
(
    SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >=15
        AND minute <=25

    INTERSECT

    SELECT license_plate FROM people WHERE id IN
        (
            SELECT person_id FROM bank_accounts WHERE account_number IN
            (
                SELECT account_number
                FROM atm_transactions
                    WHERE atm_location = "Leggett Street"
                    AND year = 2021
                    AND month = 7
                    AND day = 28
                    AND transaction_type = "withdraw"
            )
        )
);

-- The following people withrawed money and went to the bakery
-- +-------+----------------+-----------------+---------------+
-- | name  |  phone_number  | passport_number | license_plate |
-- +-------+----------------+-----------------+---------------+
-- | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +-------+----------------+-----------------+---------------+

-- Phone Calls
SELECT caller,receiver,duration FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;

-- The following made calls in the time frame
+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |

| (367) 555-5533 | (375) 555-8161 | 45       |

| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |

| (770) 555-1861 | (725) 555-3243 | 49       |

| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54       |
--

SELECT name,phone_number,passport_number,license_plate FROM people
WHERE phone_number IN
(
    SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60

    INTERSECT

    SELECT phone_number FROM people
    WHERE license_plate IN
    (
        SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >=15
            AND minute <=25

        INTERSECT

        SELECT license_plate FROM people WHERE id IN
            (
                SELECT person_id FROM bank_accounts WHERE account_number IN
                (
                    SELECT account_number
                    FROM atm_transactions
                        WHERE atm_location = "Leggett Street"
                        AND year = 2021
                        AND month = 7
                        AND day = 28
                        AND transaction_type = "withdraw"
                )
            )
    )
);

-- The following car + ATM + call
-- +-------+----------------+-----------------+---------------+
-- | name  |  phone_number  | passport_number | license_plate |
-- +-------+----------------+-----------------+---------------+
-- | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | Philip
-- | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | Robin
-- +-------+----------------+-----------------+---------------+

SELECT name,phone_number,passport_number,license_plate FROM people
WHERE phone_number =  "(375) 555-8161"
OR phone_number =  "(725) 555-3243";
-- +--------+----------------+-----------------+---------------+
-- |  name  |  phone_number  | passport_number | license_plate |
-- +--------+----------------+-----------------+---------------+
-- | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
-- | Robin  | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+----------------+-----------------+---------------+


SELECT flight_id,passport_number FROM passengers
    WHERE passport_number = 3592750733
    OR passport_number = 5773159633
    OR passport_number = 3391710505;
-- +-----------+-----------------+
-- | flight_id | passport_number |
-- +-----------+-----------------+
-- | 18        | 3592750733      | Diana
-- | 24        | 3592750733      | Diana
-- | 36        | 5773159633      | Bruce
-- | 54        | 3592750733      | Diana
-- +-----------+-----------------+

SELECT id,origin_airport_id,destination_airport_id FROM flights
WHERE id IN
    (
        SELECT flight_id FROM passengers
        WHERE passport_number = 3592750733
        OR passport_number = 5773159633
        OR passport_number = 3391710505
    )
    AND
    (
        year = 2021
        AND month = 7
        AND day = 29
    );
+----+-------------------+------------------------+
| id | origin_airport_id | destination_airport_id |
+----+-------------------+------------------------+
| 18 | 8                 | 6                      |Diana
| 36 | 8                 | 4                      |Bruce
+----+-------------------+------------------------+

SELECT city FROM airports WHERE id = 4;