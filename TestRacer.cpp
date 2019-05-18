#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>

#include "Racer.h"
//________________________________________________________________________________
Racer *r1;
Person p1("����", "��������", "������", "Ivan", "Ivanovich", "Ivanov","�","08.10.1957");
extern String udiag;
//________________________________________________________________________________
class TTestPerson : public TTestCase {
public:
	__fastcall virtual TTestPerson(System::String name) : TTestCase(name) {
	}
	virtual void __fastcall SetUp();
	virtual void __fastcall TearDown();

__published:
	void __fastcall TestGender();
	void __fastcall TestgetAge();
	void __fastcall TestgetDoB();
	void __fastcall Testgetdob();
	void __fastcall TestsetDoB();
	void __fastcall Testsetdob();

	void __fastcall TestgetName();
	void __fastcall TestgetI();
	void __fastcall TestgetSecondName();
	void __fastcall TestgetO();
	void __fastcall TestgetSurName();
	void __fastcall TestgetSURNAME();
	void __fastcall TestgetFIO();
	void __fastcall TestgetIOF();
	void __fastcall TestgetFio();
	void __fastcall TestgetioF();
	void __fastcall TestsetName();
	void __fastcall TestsetSecondName();
	void __fastcall TestsetSurName();
};

class TTestRacer : public TTestCase {
public:
	__fastcall virtual TTestRacer(System::String name) : TTestCase(name) {
	}
	virtual void __fastcall SetUp();
	virtual void __fastcall TearDown();

__published:
	void __fastcall TestgetFIScode();
	void __fastcall TestsetFIScode();
	void __fastcall TestsetPerson();
	void __fastcall TestsetRacerName();
	void __fastcall TestsetRacerSecondName();
	void __fastcall TestsetRacerSurName();
	void __fastcall TestsetRacerdob();
};

void __fastcall TTestPerson::SetUp() {
}

void __fastcall TTestPerson::TearDown() {
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestGender() {
//	String getGender(int language=0)
String s1="W",s11="�",s2="M",s21="�",ss;
	p1.setGender(s1);ss=p1.getGender(lat);
	udiag="��������� -> "+s1+" - �������� -> "+ss;
	Check(0==s1.Compare(ss),udiag);

	p1.setGender(s2);ss=p1.getGender(lat);
	udiag="��������� -> "+s2+" - �������� -> "+ss;
	Check(0==s2.Compare(ss),udiag);

	p1.setGender(s11);ss=p1.getGender(rus);
	udiag="��������� -> "+s11+" - �������� -> "+ss;
	Check(0==s11.Compare(ss),udiag);

	p1.setGender(s21);ss=p1.getGender(rus);
	udiag="��������� -> "+s21+" - �������� -> "+ss;
	Check(0==s21.Compare(ss),udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetAge() {
	// String Person::getAge(void)const
	String udiag,dobset("08.07.2008"),dobget,dobcheck("10");
	r1->setDoB(dobset);
	dobget = r1->getAge();//String Person::getAge(void)const
	udiag="��������� -> "+dobcheck+" - �������� -> "+dobget;
	Check(0==dobcheck.Compare(dobget),udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetDoB() {
	// TDate getDoB(void)
	String udiag,dobset("08.07.2008"),dobget;
	r1->setDoB(dobset);
	dobget = r1->getDoB();//String Person::getDoB(void)const
	udiag="��������� -> "+dobset+" - �������� -> "+dobget;
	Check(0==dobset.Compare(dobget),udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::Testgetdob() {
	// TDate getdob(void)
	TDate dobset("08.07.2008"),dobget;
	r1->setdob(dobset);
	dobget = r1->getdob();//TDate Person::getdob(void)const
	udiag="��������� -> "+dobset.FormatString("dd.mm.yyyy")+" - �������� -> "+dobget.FormatString("dd.mm.yyyy");
	Check(dobset==dobget,udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestsetDoB() {
	// void setDoB(String)
	String str;
	TDate dobset("08.07.2008"),dobget;
	str=dobset.FormatString("dd.mm.yyyy");
	r1->setDoB(str); // void setDoB(String)
	dobget = r1->getdob();
	udiag="��������� -> "+dobset.FormatString("dd.mm.yyyy")+" - �������� -> "+dobget.FormatString("dd.mm.yyyy");
	Check(dobget==dobset,udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::Testsetdob() {
	// void setdob(TDate dob)
	TDate dobset("08.07.2008"),dobget;
	String astr;
	r1->setdob(dobset);//test setdob(TDate dob)
	dobget = r1->getdob();
	udiag="��������� -> "+dobset.FormatString("dd.mm.yyyy")+" - �������� -> "+dobget.FormatString("dd.mm.yyyy");
	Check(dobget==dobset,udiag);
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetName() {
	// AnsiString getName(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetI() {
	// AnsiString getI(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetSecondName() {
	// AnsiString getSecondName(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetO() {
	// AnsiString getO(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetSurName() {
	// AnsiString getSurName(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetSURNAME() {
	// AnsiString getSURNAME(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetFIO() {
	// AnsiString getFIO(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetIOF() {
	// AnsiString getIOF(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetFio() {
	// AnsiString getFio(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestgetioF() {
	// AnsiString getioF(int language)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestsetName() {
	// void setName(int language, AnsiString name)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestsetSecondName() {
	// void setSecondName(int language, AnsiString secondname)
}
//______________________________________________________________________________
void __fastcall TTestPerson::TestsetSurName() {
	// void setSurName(int language, AnsiString surname)
}
//______________________________________________________________________________
void __fastcall TTestRacer::SetUp() {
}
//______________________________________________________________________________
void __fastcall TTestRacer::TearDown() {
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestgetFIScode() {
	// AnsiString getFIScode()
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetFIScode() {
	// void setFIScode(AnsiString sfis)
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetPerson() {
	// void setPerson(Person *p)
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetRacerName() {
	// void setRacerName(Person *p)
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetRacerSecondName() {
	// void setRacerSecondName(Person *p)
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetRacerSurName() {
	// void setRacerSurName(Person *p)
}
//______________________________________________________________________________
void __fastcall TTestRacer::TestsetRacerdob() {
	// void setRacerAge(Person *p)
}
//______________________________________________________________________________
static void registerTests() {
	Testframework::RegisterTest(TTestPerson::Suite());
	Testframework::RegisterTest(TTestRacer::Suite());

	r1 = new Racer;
	r1->setFIScode("123456");
	r1->setPerson(&p1);
}
#pragma startup registerTests 33
