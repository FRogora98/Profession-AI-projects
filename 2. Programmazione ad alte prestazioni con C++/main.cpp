#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

class Cliente
{
public:
    std::string nome;
    std::string cognome;
    std::string numeroTelefono;

    Cliente(std::string nome, std::string cognome, std::string numeroTelefono)
        : nome(nome), cognome(cognome), numeroTelefono(numeroTelefono) {}

    std::string serializza() const
    {
        return nome + "," + cognome + "," + numeroTelefono;
    }

    void visualizzaDettagli() const
    {
        std::cout << "Nome: " << nome << "\nCognome: " << cognome
                  << "\nNumero di Telefono: " << numeroTelefono << std::endl;
    }
};

class Interazione
{
public:
    std::string tipoInterazione;
    std::string descrizione;

    Interazione(std::string tipo, std::string descrizione)
        : tipoInterazione(tipo), descrizione(descrizione) {}

    std::string serializza() const
    {
        return tipoInterazione + "," + descrizione;
    }

    void visualizzaInterazione() const
    {
        std::cout << "Tipo di Interazione: " << tipoInterazione
                  << "\nDescrizione: " << descrizione << std::endl;
    }
};

class CRM
{
private:
    std::vector<Cliente> clienti;
    std::vector<Interazione> interazioni;

public:
    void aggiungiCliente()
    {
        std::string nome, cognome, telefono;
        std::cout << "Inserisci il nome del cliente: ";
        std::cin >> nome;
        std::cout << "Inserisci il cognome del cliente: ";
        std::cin >> cognome;
        std::cout << "Inserisci il numero di telefono: ";
        std::cin >> telefono;

        clienti.emplace_back(nome, cognome, telefono);
        std::cout << "Cliente aggiunto con successo!" << std::endl;
    }

    void visualizzaClienti() const
    {
        for (const auto &cliente : clienti)
        {
            cliente.visualizzaDettagli();
            std::cout << "-------------------" << std::endl;
        }
    }

    void modificaCliente()
    {
        if (clienti.empty())
        {
            std::cout << "Nessun cliente disponibile per la modifica." << std::endl;
            return;
        }

        std::cout << "Lista clienti disponibili per la modifica:\n";
        for (size_t i = 0; i < clienti.size(); ++i)
        {
            std::cout << i + 1 << ". " << clienti[i].nome << " " << clienti[i].cognome << " - " << clienti[i].numeroTelefono << std::endl;
        }

        int scelta;
        std::cout << "Inserisci il numero del cliente che desideri modificare: ";
        std::cin >> scelta;

        if (scelta < 1 || scelta > clienti.size())
        {
            std::cout << "Scelta non valida!" << std::endl;
            return;
        }

        Cliente &clienteSelezionato = clienti[scelta - 1];
        std::string nuovoNome, nuovoCognome, nuovoTelefono;

        std::cout << "Inserisci il nuovo nome (o premi Enter per mantenere \"" << clienteSelezionato.nome << "\"): ";
        std::cin.ignore();
        std::getline(std::cin, nuovoNome);
        if (!nuovoNome.empty())
        {
            clienteSelezionato.nome = nuovoNome;
        }

        std::cout << "Inserisci il nuovo cognome (o premi Enter per mantenere \"" << clienteSelezionato.cognome << "\"): ";
        std::getline(std::cin, nuovoCognome);
        if (!nuovoCognome.empty())
        {
            clienteSelezionato.cognome = nuovoCognome;
        }

        std::cout << "Inserisci il nuovo numero di telefono (o premi Enter per mantenere \"" << clienteSelezionato.numeroTelefono << "\"): ";
        std::getline(std::cin, nuovoTelefono);
        if (!nuovoTelefono.empty())
        {
            clienteSelezionato.numeroTelefono = nuovoTelefono;
        }

        std::cout << "Cliente aggiornato con successo!" << std::endl;
    }

    void eliminaCliente()
    {
        std::string nome;
        std::cout << "Inserisci il nome del cliente da eliminare: ";
        std::cin >> nome;

        std::vector<int> clientiTrovati;
        for (size_t i = 0; i < clienti.size(); ++i)
        {
            if (clienti[i].nome == nome)
            {
                clientiTrovati.push_back(i);
                std::cout << clientiTrovati.size() << ". " << clienti[i].nome << " " << clienti[i].cognome << " - " << clienti[i].numeroTelefono << std::endl;
            }
        }

        if (clientiTrovati.empty())
        {
            std::cout << "Nessun cliente trovato con il nome " << nome << "." << std::endl;
            return;
        }

        int scelta;
        std::cout << "Inserisci il numero del cliente che desideri eliminare: ";
        std::cin >> scelta;

        if (scelta < 1 || scelta > clientiTrovati.size())
        {
            std::cout << "Scelta non valida!" << std::endl;
            return;
        }

        clienti.erase(clienti.begin() + clientiTrovati[scelta - 1]);
        std::cout << "Cliente eliminato con successo!" << std::endl;
    }

    void ricercaCliente() const
    {
        std::string nome;
        std::cout << "Inserisci il nome del cliente da cercare: ";
        std::cin >> nome;

        std::vector<int> clientiTrovati;
        for (size_t i = 0; i < clienti.size(); ++i)
        {
            if (clienti[i].nome == nome)
            {
                clientiTrovati.push_back(i);
                std::cout << clientiTrovati.size() << ". " << clienti[i].nome << " " << clienti[i].cognome << " - " << clienti[i].numeroTelefono << std::endl;
            }
        }

        if (clientiTrovati.empty())
        {
            std::cout << "Nessun cliente trovato con il nome " << nome << "." << std::endl;
            return;
        }

        int scelta;
        std::cout << "Inserisci il numero del cliente che desideri visualizzare: ";
        std::cin >> scelta;

        if (scelta < 1 || scelta > clientiTrovati.size())
        {
            std::cout << "Scelta non valida!" << std::endl;
            return;
        }

        clienti[clientiTrovati[scelta - 1]].visualizzaDettagli();
    }

    void aggiungiInterazione()
    {
        std::string tipo, descrizione;
        std::cout << "Inserisci il tipo di interazione (Appuntamento/Contratto): ";
        std::cin >> tipo;
        std::cout << "Inserisci una breve descrizione: ";
        std::cin.ignore();
        std::getline(std::cin, descrizione);

        interazioni.emplace_back(tipo, descrizione);
        std::cout << "Interazione aggiunta con successo!" << std::endl;
    }

    void visualizzaInterazioni() const
    {
        for (const auto &interazione : interazioni)
        {
            interazione.visualizzaInterazione();
            std::cout << "-------------------" << std::endl;
        }
    }

    void salvaDatiSuFile(const std::string &nomeFile) const
    {
        std::filesystem::path percorsoCorrente = std::filesystem::current_path();
        std::string percorsoCompleto = (percorsoCorrente / nomeFile).string();

        std::ofstream file(percorsoCompleto);
        if (!file.is_open())
        {
            std::cerr << "Errore nell'apertura del file per il salvataggio! Verifica il percorso: " << percorsoCompleto << std::endl;
            return;
        }

        std::cout << "Salvataggio file in: " << percorsoCompleto << std::endl;

        for (const auto &cliente : clienti)
        {
            file << cliente.serializza() << "\n";
        }

        for (const auto &interazione : interazioni)
        {
            file << "Interazione," << interazione.serializza() << "\n";
        }

        file.close();
        std::cout << "Dati salvati su file con successo!" << std::endl;
    }

    void caricaDatiDaFile(const std::string &nomeFile)
    {
        std::filesystem::path percorsoCorrente = std::filesystem::current_path();
        std::string percorsoCompleto = (percorsoCorrente / nomeFile).string();

        std::ifstream file(percorsoCompleto);
        if (!file.is_open())
        {
            std::cerr << "Errore nell'apertura del file per il caricamento! Verifica il percorso: " << percorsoCompleto << std::endl;
            return;
        }

        clienti.clear();
        interazioni.clear();

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string tipo, parte1, parte2, parte3;

            std::getline(ss, tipo, ',');
            if (tipo == "Interazione")
            {
                std::getline(ss, parte1, ',');
                std::getline(ss, parte2);
                interazioni.emplace_back(parte1, parte2);
            }
            else
            {
                parte1 = tipo;
                std::getline(ss, parte2, ',');
                std::getline(ss, parte3);
                clienti.emplace_back(parte1, parte2, parte3);
            }
        }

        file.close();
        std::cout << "Dati caricati da file con successo!" << std::endl;
    }
};

void mostraMenu()
{
    std::cout << "\n--- InsuraPro Solutions ---\n";
    std::cout << "1. Aggiungi cliente\n";
    std::cout << "2. Visualizza clienti\n";
    std::cout << "3. Modifica cliente\n";
    std::cout << "4. Elimina cliente\n";
    std::cout << "5. Ricerca cliente\n";
    std::cout << "6. Aggiungi interazione\n";
    std::cout << "7. Visualizza interazioni\n";
    std::cout << "8. Salva dati su file\n";
    std::cout << "9. Carica dati da file\n";
    std::cout << "0. Esci\n";
}

int main()
{
    CRM crm;
    int scelta;
    std::string nomeFile = "dati_clienti.csv";

    do
    {
        mostraMenu();
        std::cout << "Inserisci la tua scelta: ";
        std::cin >> scelta;

        switch (scelta)
        {
        case 1:
            crm.aggiungiCliente();
            break;
        case 2:
            crm.visualizzaClienti();
            break;
        case 3:
            crm.modificaCliente();
            break;
        case 4:
            crm.eliminaCliente();
            break;
        case 5:
            crm.ricercaCliente();
            break;
        case 6:
            crm.aggiungiInterazione();
            break;
        case 7:
            crm.visualizzaInterazioni();
            break;
        case 8:
            crm.salvaDatiSuFile(nomeFile);
            break;
        case 9:
            crm.caricaDatiDaFile(nomeFile);
            break;
        case 0:
            std::cout << "Uscita dal programma." << std::endl;
            break;
        default:
            std::cout << "Scelta non valida!" << std::endl;
        }
    } while (scelta != 0);

    return 0;
}
