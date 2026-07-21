#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; i++)
        this->_templates[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const & src)
{
    for (int i = 0; i < 4; i++)
    {
        if (src._templates[i])
            this->_templates[i] = src._templates[i]->clone();
        else
            this->_templates[i] = NULL;
    }
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; i++)
    {
        if (this->_templates[i])
            delete this->_templates[i];
    }
}

MateriaSource & MateriaSource::operator=(MateriaSource const & rhs)
{
    if (this != &rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            if (this->_templates[i])
                delete this->_templates[i];
            if (rhs._templates[i])
                this->_templates[i] = rhs._templates[i]->clone();
            else
                this->_templates[i] = NULL;
        }
    }
    return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (!this->_templates[i])
        {
            this->_templates[i] = m;
            return;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; i++)
    {
        if (this->_templates[i] && this->_templates[i]->getType() == type)
            return this->_templates[i]->clone();
    }
    return NULL;
}
