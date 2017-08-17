#include "utils/StreamGroupWriter.h"

namespace librcsscontroller
{
    StreamGroupWriter::StreamGroupWriter(std::vector<std::ostream*> group, 
            const std::string& identifier, 
            const std::unordered_map<std::ostream*, StreamWriter*>& prefixes)
        : group_{group}, identifier_{identifier}, stream_prefixes_{prefixes}
    { }

    StreamGroupWriter::StreamGroupWriter(std::vector<std::ostream*> group)
        : StreamGroupWriter(group, "", {})
    { }

}