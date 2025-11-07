#pragma once

#include <unistd.h>

#include "AccessControl.hh"
#include "Scene.hh"

using namespace std;

int Send(int Sk2Server, const char *sMesg);


// /*!
//  * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
//  *
//  * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
//  * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
//  * informacje o aktualnej pozycji wszystkich obiektów.
//  */
// class Sender {
//   /*!
//    * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
//    * 
//    * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
//    * W przypadku wartości \p true, pętla wątku będzie wykonywana.
//    * Natomiast wartość \p false powoduje przerwanie pętli.
//    */
//    volatile bool    _ContinueLooping = true;
//   /*!
//    * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
//    */
//    int             _Socket = 0;
//   /*!
//    * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
//    *        poleceń do serwera graficzneg.
//    */
//    AccessControl  *_aControl = nullptr;
//     shared_ptr<Scene> _scene;
  
//  public:
//   /*!
//    * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
//    *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
//    */
//    Sender(int Socket, AccessControl *aControl, shared_ptr<Scene> scene): _Socket(Socket), _aControl(aControl), _scene(scene) {}

//   /*!
//    * \brief Sprawdza, czy pętla wątku może być wykonywana.
//    * 
//    * Sprawdza, czy pętla wątku może być wykonywana.
//    * \retval true - pętla wątku może być nadal wykonywana.
//    * \retval false - w przypadku przeciwnym.
//    */
//    bool ShouldCountinueLooping() const { return _ContinueLooping; }
//   /*!
//    * \brief Powoduje przerwanie działania pętli wątku.
//    *
//    * Powoduje przerwanie działania pętli wątku.
//    * \warning Reakcja na tę operację nie będize natychmiastowa.
//    */  
//    void CancelCountinueLooping() { _ContinueLooping = false; }

//   /*!
//    * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
//    *
//    * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
//    * wysyła je do serwera.
//    * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
//    *                     wysyłane są polecenia.
//    */
//     void Watching_and_Sending() {
//         while (ShouldCountinueLooping()) {
//             if (!_aControl->IsChanged())  { usleep(10000); continue; }
//             _aControl->LockAccess();

//             //------- Przeglądanie tej kolekcji to uproszczony przykład

//             for (const auto &pair : _scene->GetObjs()) {
//                 const auto &rObj = pair.second;

//                 cout << rObj->GetStateDesc();
//                 Send(_Socket,rObj->GetStateDesc().c_str()); // Tu musi zostać wywołanie odpowiedniej
//                                             // metody/funkcji gerującej polecenia dla serwera.
//             }

//             _aControl->CancelChange();
//             _aControl->UnlockAccess();
//         }
//     }
  
// };
// void Fun_CommunicationThread(Sender  *pSender);