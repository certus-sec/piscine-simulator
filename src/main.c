#include "simulator.h"

int main(void)
{
    t_session *session;
    int choice;

    init_rng();
    banner_welcome();

    while (1)
    {
        choice = menu_main();
        if (choice == 0)
            break;
        if (choice < 1 || choice > 4)
            continue;

        session = session_new();
        runner_start(session, choice - 1);

        if (session_is_complete(session))
            certificate_print(session);

        session_destroy(session);
    }

    return 0;
}
