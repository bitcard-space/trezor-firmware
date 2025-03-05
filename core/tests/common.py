
from tests.trezor import unittest  # noqa: F401
from trezor.typing import Any, Awaitable
from ubinascii import hexlify, unhexlify  # noqa: F401

from trezor import utils  # noqa: F401

from micropython import const
HARDENED = const(0x8000_0000)


def H_(x: int) -> int:
    """
    Shortcut function that "hardens" a number in a BIP44 path.
    """
    return x | HARDENED


def await_result(task: Awaitable) -> Any:
    value = None
    while True:
        try:
            result = task.send(value)
        except StopIteration as e:
            return e.value

        if result:
            value = await_result(result)
        else:
            value = None
