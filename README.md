# ATM Simulator (C++)  
**Object-Oriented Programming Course Project**

본 프로젝트는 **객체지향프로그래밍(Object-Oriented Programming)** 강의의 과제로 수행한  
C++ 기반 **ATM 시뮬레이터**입니다.  
은행(Bank), 계좌(Account), ATM을 클래스로 모델링하여,  
객체 간 상호작용과 책임 분리를 중심으로 시스템을 설계하는 데 목적을 두었습니다.

---

## 📌 Project Overview

이 프로젝트는 실제 ATM 사용 시나리오를 기반으로 다음을 구현합니다:

- 계좌(Account)와 은행(Bank)의 객체화
- ATM 기능을 클래스 계층 구조로 설계
- 단일 은행 ATM과 다중 은행 ATM의 차이 표현
- 예금, 출금, 송금 기능 구현
- 은행 간 거래 시 수수료 정책 반영
- 한국어 / 영어 UI 분리
- 관리자 모드를 통한 거래 내역 관리

강의에서 학습한 **Abstraction, Encapsulation, Inheritance, and Polymorphism** 개념을 실제 프로그램 구조에 적용했습니다.

---

## 🧱 Class Design

### 1. `Account`
- 사용자 계좌 정보를 표현하는 클래스
- 은행 종류, 카드 번호, 계좌 번호, 비밀번호, 잔액 관리
- 잔액 변경 로직 캡슐화

### 2. `Bank`
- 여러 계좌를 중앙에서 관리하는 클래스
- 카드 번호 및 계좌 번호 기반 계좌 검색
- 입금 / 출금 / 송금 시 계좌 상태 업데이트
- 계좌 유효성 검증 담당

### 3. `ATM` (Base Class)
- ATM의 공통 속성과 기능 정의
- 사용자 인증(Authorization)
- 거래 흐름(Transaction) 관리
- 거래 기록 저장 및 관리자 기능 제공

### 4. `single_ATM`
- 주거래 은행 계좌만 허용하는 ATM
- 타 은행 계좌 사용 제한

### 5. `multi_ATM`
- 여러 은행 계좌 사용 가능
- 은행 간 거래 시 추가 수수료 부과

---

## 💳 Implemented Transactions

- **Deposit (예금)**  
  - 현금 / 수표 선택
  - 금액권 종류 및 개수 입력

- **Withdrawal (출금)**  
  - 만원 단위 출금 제한
  - ATM 보유 현금 및 계좌 잔액 검사

- **Transfer (송금)**  
  - 현금 송금 / 계좌 송금
  - 동일 은행 / 타 은행 수수료 차등 적용

---

## 🌐 Language Support

- Korean
- English

ATM 설정에 따라:
- 단일 언어 ATM (`uni`)
- 이중 언어 ATM (`bi`) 선택 가능

---

## 🔐 Management & Security

- 비밀번호 입력 횟수 제한
- 관리자 카드(AdminCard)를 통한:
  - 전체 거래 내역 조회
  - 거래 기록을 텍스트 파일(`Transaction History.txt`)로 저장

---

## ▶️ How to Run

```bash
g++ atm_simulator.cpp -o atm_simulator
./atm_simulator
```

---

실행 후 프로그램 흐름은 다음과 같습니다:

- 계좌 생성  
- ATM 선택  
- 사용자 인증 및 거래 수행  

---

## 🎯 Learning Objectives

본 프로젝트를 통해 다음과 같은 객체지향 프로그래밍 역량을 학습했습니다:

- 객체지향 설계의 중요성 이해  
- 클래스 간 책임 분리 (`Account` / `Bank` / `ATM`)  
- 상속을 통한 기능 확장 (single ATM vs. multi ATM)  
- 실제 시스템 요구사항을 코드 구조로 모델링하는 방법  
- 절차적 접근이 아닌 **객체 중심 사고 방식**의 적용  

---

## 📌 Notes

- 본 프로젝트는 **객체지향프로그래밍 강의의 교육 목적 과제**입니다.  
- 실제 금융 시스템과는 다르며, 보안 및 예외 처리는 단순화되어 있습니다.  
- 카드 번호와 계좌 번호는 프로그램 실행 시 **랜덤으로 생성**됩니다.  

---

## ✨ Summary

이 프로젝트는  
> **“객체지향 개념을 단순한 예제를 넘어 하나의 시스템으로 확장하여 설계해보는 경험”**  

을 목표로 한 ATM 시뮬레이터입니다.  
기능 구현 자체보다는, **클래스 구조와 객체 간 관계 설계**에 중점을 두었습니다.
