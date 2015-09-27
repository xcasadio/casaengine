#ifndef EXCEPTION_H
#define EXCEPTION_H


#include "CA_Export.h"
#include <exception>
#include <string>
#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe de base pour les exceptions
    ////////////////////////////////////////////////////////////
    class CA_EXPORT CException : 
		public std::exception,
		public AllocatedObject<CException>
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        CException(const std::string& Message = "");

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        virtual ~CException() throw();

        //----------------------------------------------------------
        // Renvoie le message associé à l'exception
        //----------------------------------------------------------
        virtual const char* what() const throw();

    private :

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        std::string m_Message; ///< Message décrivant l'exception
    };


    ////////////////////////////////////////////////////////////
    /// Exception lancée si une condition n'est pas vérifiée
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT CAssertException : public CException
    {
        CAssertException(const std::string& File, int Line, const std::string& Message);
    };

    ////////////////////////////////////////////////////////////
    /// Exception lancée lors d'une anomalie d'allocation mémoire
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT CBadDelete : public CException
    {
        CBadDelete(const void* Ptr, const std::string& File, int Line, bool NewArray);
    };


    ////////////////////////////////////////////////////////////
    /// Exception lancée lors d'erreur de chargement de fichiers
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT CLoadingFailed : public CException
    {
        CLoadingFailed(const std::string& File, const std::string& Message);
    };


    ////////////////////////////////////////////////////////////
    /// Exception lancée lors de saturations de mémoire
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT COutOfMemory : public CException
    {
        COutOfMemory(const std::string& Message);
    };


    ////////////////////////////////////////////////////////////
    /// Exception lancée lors de l'utilisation d'une caractéristique non supportée
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT CUnsupported : public CException
    {
        CUnsupported(const std::string& Feature);
    };


    ////////////////////////////////////////////////////////////
    /// Exception lancée lors d'une erreur de conversion
    ////////////////////////////////////////////////////////////
    struct CA_EXPORT CBadConversion : public CException
    {
        CBadConversion(const std::string& Error);
    };

	////////////////////////////////////////////////////////////
	/// 
	////////////////////////////////////////////////////////////
	struct CA_EXPORT CArgumentNullException : public CException
	{
		CArgumentNullException(const std::string& Error);
	};

	////////////////////////////////////////////////////////////
	/// 
	////////////////////////////////////////////////////////////
	struct CA_EXPORT CArgumentException : public CException
	{
		CArgumentException(const std::string& Error);
	};

	////////////////////////////////////////////////////////////
	/// 
	////////////////////////////////////////////////////////////
	struct CA_EXPORT CArgumentOutOfRangeException : public CException
	{
		CArgumentOutOfRangeException(const std::string& Error);
	};

	/**
	 * 
	 */
	struct CA_EXPORT CNotImplementedException : public CException
	{
		CNotImplementedException(const std::string& Error);
	};

	/**
	 * 
	 */
	struct CA_EXPORT CUnknownObjectException : public CException
	{
		CUnknownObjectException(const std::string& Error);
	};

} // namespace CasaEngine


#endif // EXCEPTION_H
